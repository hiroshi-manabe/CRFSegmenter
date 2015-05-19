#ifndef HOCRF_HIGH_ORDER_CRF_TRIE_H_
#define HOCRF_HIGH_ORDER_CRF_TRIE_H_

#include "types.h"

#include <cassert>
#include <memory>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::vector;

template<typename L>
struct TrieNode {
    L label;
    vector<TrieNode> children;
    int value;

    TrieNode::TrieNode(L label) : label(label) {
        value = -1;
    }
    
    size_t TrieNode::getChildIndex(L label) const {
        size_t index = 0;
        if (children.size() < 32) {
            for (index = 0; index < children.size() && label > children[index].label; ++index);
            return index;
        } else {
            size_t start = 0;
            size_t end = children.size();
            while (start < end) {
                index = (start + end) / 2;
                if (label - children[index].label > 0) {
                    start = index + 1;
                } else {
                    end = index;
                }
            }
            return start;
        }
    }

    TrieNode *TrieNode::getChild(size_t index, L label) const {
        if (index < children.size() && children[index].label == label) {
            return const_cast<TrieNode *>(&children[index]);
        }
        return 0;
    }

    TrieNode *addChild(size_t index, L label) {
        assert(index >= 0 && index <= children.size());
        return &(*children.emplace(children.begin() + index, label));
    }
};

template<typename L>
void visitValidNodesRec(vector<L> &labels, TrieNode<L> *node, TrieNode<L> *validParent, void (*proc)(L *, size_t, int, int, void *), void *data) {
    TrieNode<L>* newParent;
    if (node->value != -1) {
        (*proc)(labels.data(), labels.size(), node->value, validParent->value, data);
        newParent = node;
    } else {
        newParent = validParent;
    }
    for (TrieNode<L> &child : node->children) {
        labels.push_back(child.label);
        visitValidNodesRec(labels, &child, newParent, proc, data);
        labels.pop_back();
    }
}

template<typename L>
class Trie {
public:
    Trie::Trie() : rootNode(-1) {
    }

    Trie::~Trie() {
    }

    int Trie::findOrInsert(const L *data, size_t size, int value) {
        TrieNode<L> *node = &rootNode;
        for (size_t i = 0; i < size; ++i) {
            size_t index = node->getChildIndex(data[i]);
            TrieNode<L> *nextNode = node->getChild(index, data[i]);
            if (!nextNode) {
                nextNode = node->addChild(index, data[i]);
            }
            node = nextNode;
        }
        if (node->value == -1) {
            node->value = value;
        }
        return node->value;
    }

    int Trie::find(const L *data, size_t size) const {
        const TrieNode<L> *node = &rootNode;
        for (size_t i = 0; i < size; ++i) {
            node = node->getChild(node->getChildIndex(data[i]), data[i]);
            assert(node != 0);
        }
        return node->value;
    }

    int Trie::findLongestMatch(const L *data, size_t size) const {
        const TrieNode<L> *node = &rootNode;
        for (size_t i = 0; i < size; ++i) {
            TrieNode<L> *nextNode = node->getChild(node->getChildIndex(data[i]), data[i]);
            if (!nextNode) {
                return node->value;
            }
            node = nextNode;
        }
        return node->value;
    }

    void Trie::visitValidNodes(void (*proc)(L *, size_t, int, int, void *), void *data) {
        vector<L> v;
        visitValidNodesRec(v, &rootNode, &rootNode, proc, data);
    }

private:
    TrieNode<L> rootNode;
};

}  // namespace HighOrderCRF

#endif  // HOCRF_HIGH_ORDER_CRF_TRIE_H
