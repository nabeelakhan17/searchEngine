#ifndef ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_AVLTREE_H
#define ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_AVLTREE_H

#include <algorithm>
#include <stdexcept>
#include <queue>
using namespace std;

/**
 * @brief Simple implementation of an (unbalanced) binary search tree
 *
 * @tparam Comparable
 */
template <typename Comparable>
class AvlTree
{
    // define node structure as a nested class
private:
    class AvlNode
    {
    public:
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;
    int size;

public:
    /**
     * @brief Default Constructor creates an empty Binary Search Tree
     *
     */
    AvlTree() : root{nullptr}, size{0}
    {
    }

    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     *
     */
    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    /**
     * @brief Rule-of-3 Part 2: Destroy the Binary Search Tree object using the internal
     *   function makeEmpty().
     */
    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * @brief Rule-of-3 Part 3: Copy assignment
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);

        return *this;
    }

    /**
     * @brief Test if the tree is logically empty.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * @brief Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    /**
     * @brief Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    /**
     * @brief Returns true if x is found in the tree using an internal function.
     */
    bool contains(const Comparable &x) const
    {
        return find(x, root) != nullptr;
    }

    /**
     * @brief Print the tree contents in sorted order (i.e., inorder traversal).
     * This is Tree Sort.
     */
    void printTreeSort(ostream &out = cout) const
    {
        if (isEmpty())
            out << "Empty tree" << endl;
        else
            printTreeSort(root, out);
    }

    /**
     * @brief Print the tree structure (for debugging)
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

    /**
     * @brief Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * @brief Find the smallest item in the tree.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw std::runtime_error("tree is empty!");
        return findMin(root)->element;
    }

    /**
     * @brief find the largest item in the tree.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw std::runtime_error("tree is empty!");
        return findMax(root)->element;
    }

    int maxDepth()
    {
        return maxDepth(root, 0);
    }

    double avgDepth()
    {
        throw std::runtime_error("Not implemented yet!");
        return 0.0;
    }

    void printTreeByLevel(ostream &out = cout) const
    {
        printTreeByLevel(root, out);
    }

    AvlNode returnNode(const Comparable &x)
    {
        return find(x, root);
    }

    Comparable find(const Comparable &x)
    {
        return findVal(x, root);
    }

    void printTree(ostream &out)
    {
        printTree(out, root);
    }

    int getSize()
    {
        return getSize(root);
    }

private:

    /**
     * @brief Returns how many nodes are in the tree
     * 
     */
    int getSize(AvlNode *t)
    {
        if (t == nullptr)
            return 0;
        int l = getSize(t->left);
        int r = getSize(t->right);
    
        return 1 + l + r;
    }
    
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    void rotateWithLeftChild(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    // Case :
    void rotateWithRightChild(AvlNode *&k1)
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper
                                            // but the search less efficient.

    // Called to ensure an equal height amoung the AVL Tree
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t a non-const reference to the node that roots the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t)
    {
        // found an empty spot? insert a new node
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr};
            size++;
        }
        // recursively find the insert position
        else if (t->element > x)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
        {
        }; // Duplicate: element == x; do nothing... we could do other things.

        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, AvlNode *&t) 
    {
        // Recursively find the node to delete using binary search.

        if (t == nullptr)
            return; // Item not found; do nothing

        // must be in left subtree
        if (t->element > x)
            return remove(x, t->left);

        // must be in right subtree
        if (t->element < x)
            return remove(x, t->right);

        // we get here only for t->element == x

        // Cases:
        // A. No children: Just remove the node.
        if (t->left == nullptr && t->right == nullptr)
        {
            delete t;
            t = nullptr;
            size--;
            return;
        }

        // C. Two children case: replace element with the smallest element in the right subtree.
        if (t->left != nullptr && t->right != nullptr)
        {
            AvlNode *replacement = removeMin(t->right);
            replacement->right = t->right;
            replacement->left = t->left;

            delete t;
            t = replacement;
            size--;
            return;
        }

        // B. One child case: replace the node with the only child.
        AvlNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        size--;
        delete oldNode;

        balance(t);
    }

    /**
     * Internal method to find, remove and return the smallest item in a subtree t.
     */
    AvlNode *removeMin(AvlNode *&t)
    {
        // recursive implementation
        // special case: no root node
        if (t == nullptr)
            return nullptr;

        // special case: root is the minimum
        if (t->left == nullptr)
        {
            AvlNode *min = t;
            t = t->right;
            size--;
            return min;
        }

        // traverse down left to the leaf
        if (t->left->left == nullptr)
        {
            AvlNode *min = t->left;
            t->left = min->right;
            size--;
            return min;
        }

        return removeMin(t->left);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const
    {
        // recursive implementation
        // special case: no root node
        if (t == nullptr)
            return nullptr;

        // traverse down left to the leaf
        if (t->left == nullptr)
            return t;

        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode *findMax(AvlNode *t) const
    {
        // iterative implementation of going down right to the leaf.
        // special case: no root node
        if (t == nullptr)
            return nullptr;

        // traverse down right to the leaf
        while (t->right != nullptr)
            t = t->right;
        return t;
    }

    /**
     * Internal method to find a node.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    AvlNode *find(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        // recursion
        if (t->element > x)
            return find(x, t->left);

        if (t->element < x)
            return find(x, t->right);

        // we have t->element == x
        return t; // Match
    }
    /****** NONRECURSIVE VERSION*************************
    BinaryNode* find( const Comparable & x, BinaryNode *t ) const
        {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return t;    // Match
            return nullptr;   // No match
        }
    *****************************************************/

    /**
     * Internal method to clone subtree.
     * -> preorder traversal (NLR)
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        // recursion
        return new AvlNode{t->element, clone(t->left), clone(t->right)};
    }

    /**
     * Internal method to make subtree empty uses postorder traversal (LRN)
     * Note the pointer reference for t.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        // recursion
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
        size = 0;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * This is inorder traversal (LNR)
     */
    void printTreeSort(AvlNode *t, ostream &out) const
    {
        if (t == nullptr)
            return;

        // recursion
        printTreeSort(t->left, out);
        out << t->element << endl;
        printTreeSort(t->right, out);
    }

    /**
     *  Pretty print the tree structure
     *  Uses preorder traversal with R and L swapped (NRL)
     *
     *  Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const string &prefix, AvlNode *node, bool isRight) const
    {
        if (node == nullptr)
            return;

        // N: print the value of the node
        cout << prefix;
        cout << (isRight ? "├──" : "└──");
        cout << node->element << "\n";

        // R, L: enter the next tree level - right and left branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    /**
     * Internal method to print a subtree rooted.
     * This is level-order traversal.
     * We use a loop and a queue an auxiliary data structure to remember what node to process next.
     */
    void printTreeByLevel(AvlNode *t, ostream &out) const
    {
        if (t == nullptr)
            return;

        AvlNode *current;
        queue<AvlNode *> q;

        // start with the root node in the queue
        q.push(t);

        while (!q.empty())
        {
            // take the next node from the queue
            current = q.front();
            q.pop();
            out << current->element << " ";

            // add children to the queue
            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }
    }

    /**
     * maxDepth = height of the node
     *
     * -> postorder traversal (LRN)
     */
    int maxDepth(AvlNode *t, int depth)
    {
        if (t == nullptr)
            return depth;

        // traverse down
        return (std::max(maxDepth(t->left, depth + 1),
                         maxDepth(t->right, depth + 1)));
    }

    void printTree(ostream &out, AvlNode *n)
    {
        if (n != nullptr)
        {
            out << n->data << endl;
            printTree(out, n->left);
            printTree(out, n->right);
        }
    }
   //avl tree finds the value that is placed in the parameter in the AVl tree
    Comparable findVal(const Comparable &val, AvlNode *curr)
    {
        if (curr == nullptr)
        {
            Comparable temp;
            return temp;
        }
        else if (curr->element == val)
        {
            return curr->element;
        }
        else if (curr->element > val)
        {
            return findVal(val, curr->left);
        }
        else
        {
            return findVal(val, curr->right);
        }
    }
};

#endif