#include "UnionFind.h"
#include "Copier.h"

#include "loguru.hpp"
#include <algorithm>
#include <list>
#include <string>

namespace { // Anonymous namespace for local helpers
bool verbose = false;

bool equalType(std::shared_ptr<TipType> t1, std::shared_ptr<TipType> t2) {
  return *(t1.get()) == *(t2.get());
}
} // namespace

// Check Union-Find data structure invariants
void UnionFind::invariant() {
    // No two edges in the Union-Find structure should the same originating
    // TipType
    for(auto outerIter = edges.begin(); outerIter != edges.end(); outerIter++) {
        const auto& edge1 = *outerIter;
        auto innerIter = outerIter;
        innerIter++;
        for(; innerIter != edges.end(); innerIter++) {
            const auto& edge2 = *innerIter;
            if(equalType(edge1.first, edge2.first)) {
                LOG_S(3) << "UnionFind invariant violated found pair of edges: "
                         << *edge1.first << "(" << edge1.first.get() << ") => "
                         << *edge1.second << " and " << *edge2.first << "("
                         << edge2.first.get() << ") => " << *edge2.second;
                assert(!equalType(edge1.first, edge2.first));
            }
        }
    }
}

std::shared_ptr<TipType> UnionFind::lookup(std::shared_ptr<TipType> t) {
  for (auto const &edge : edges) {
    if (equalType(t, edge.first)) {
      return edge.second;
    }
  }
  return nullptr;
}

UnionFind::UnionFind(std::vector<std::shared_ptr<TipType>> seed) {
  for (auto &term : seed) {
    smart_insert(term);
  }
  invariant();
}

void UnionFind::add(std::vector<std::shared_ptr<TipType>> seed) {
  for (auto &term : seed) {
    smart_insert(term);
  }
  invariant();
}

std::ostream &operator<<(std::ostream &os, const UnionFind &obj) {
  return obj.print(os);
}

std::ostream &UnionFind::print(std::ostream &out) const {
  std::set<std::string> edgeSet;
  for (auto edge : edges) {
    std::stringstream edgeStr;
    edgeStr << "  " << *edge.first << "(" << edge.first.get() << ")"
            << " => " << *edge.second;
    edgeSet.insert(edgeStr.str());
  }
  out << "UnionFind edges {\n";
  for (auto es : edgeSet) {
    out << es << "\n";
  }
  out << "}";
  return out;
}

std::shared_ptr<TipType> UnionFind::find(std::shared_ptr<TipType> t) {
  LOG_S(3) << "UnionFind looking for representive of " << *t;

  t = smart_insert(t);

  auto parent = t;
  while (!equalType(get_parent(parent), parent)) {
    parent = get_parent(parent);
  }

  LOG_S(3) << "UnionFind found representative " << *parent;

  invariant();

  return parent;
}

void UnionFind::quick_union(std::shared_ptr<TipType> t1,
                            std::shared_ptr<TipType> t2) {
  t1 = smart_insert(t1);
  t2 = smart_insert(t2);

  auto t1_root = find(t1);
  auto t2_root = find(t2);

  // semantics-based insert
  for (auto const &edge : edges) {
    // THINK
    if (equalType(t1_root, edge.first)) {
      LOG_S(3) << "UnionFind replacing " << *edge.first << " => "
               << *edge.second << " with " << *t1_root << " => " << *t2_root;
      edges.erase(edge.first);
      edges.insert(
          std::pair<std::shared_ptr<TipType>, std::shared_ptr<TipType>>(
              t1_root, t2_root));
      break;
    }
  }

  invariant();
}

bool UnionFind::connected(std::shared_ptr<TipType> t1,
                          std::shared_ptr<TipType> t2) {
  return *find(t1) == *find(t2);
} // LCOV_EXCL_LINE

/*! \fn get_parent
 *
 * Unification ensures that the forest that includes all relevant type nodes.
 * A tree within the forest is traversed by directed edges to the parent.
 * During closure of terms, new type nodes may be generated by substitution.
 * When they are encountered they are added to the forest.
 */
std::shared_ptr<TipType> UnionFind::get_parent(std::shared_ptr<TipType> t) {
  auto parent = lookup(t);

  if (parent != nullptr)
    return parent;

  auto inserted = smart_insert(t);

  invariant();

  return inserted;
}

/**
 * Inserts should be based on the dereferenced value.
 */
std::shared_ptr<TipType> UnionFind::smart_insert(std::shared_ptr<TipType> t) {
  if (t == nullptr) {
    throw std::invalid_argument("Refusing to insert a nullptr into the map.");
  }

  if (lookup(t) != nullptr)
    return lookup(t);

  LOG_S(3) << "UnionFind adding " << *t << " to graph";
  edges.insert(
      std::pair<std::shared_ptr<TipType>, std::shared_ptr<TipType>>(t, t));

  invariant();

  return t;
}
