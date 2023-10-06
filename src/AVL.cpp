#include "AVL.h"

AVL::Node* AVL::insert(Node* root, string name, int ID, int level) {

    // Base case: found where the node should be inserted
    if (root == nullptr){
        cout << "successful" << endl;
        return new Node(name, ID, level);
    }

    // Current node is empty, keep traversing to where it should be inputted
    else if (ID < root->UFID){
        root->left = insert(root->left, name, ID, level+1);
    }
    else if (ID > root->UFID){
        root->right = insert(root->right, name, ID, level+1);
    }
    // The ID is never less than or greater than, means its already in the Tree, dont add it
    else{
        cout << "unsuccessful" << endl;
        return root;
    }

    // Call on function to update the balance factors before checking to see if tree should be rotated
    updateBalanceFactor(root);

    // Is the tree right heavy
    if (root->balanceFactor < -1){
        // Is the tree's right subtree left heavy or right heavy
        if (root->right->balanceFactor >= 1){
            // Perform Right Left rotation on appropriate nodes
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
        else{
            // Perform left rotation on the node
            root = leftRotate(root);
        }
    }
    // Is the tree left heavy
    else if (root->balanceFactor > 1){
        // Is the tree's left subtree right heavy or left heavy
        if (root->left->balanceFactor <= -1){
            // Perform Left Right rotation on appropriate nodes
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
        else{
            // Perform right rotation on the node
            root = rightRotate(root);
        }
    }

    // Return the root so the pointers are all right
    return root;
}

void AVL::printInorder(Node* root, int &target, int &count, int &foundID, bool print) {
    // Base case, we've reached the end go back
    if (root == nullptr){
        cout<< "";
    }
    else{
        // Search the left subtree to the end
        printInorder(root->left, target, count, foundID, print);
        // We are at the node, print out its data
        count++;
        if (print){
            cout<< root->name << ",";
        }
        else if (count == target){
            foundID = root->UFID;
        }
        //cout << "BALANCE FACTOR " << root->balanceFactor << "     LEVEL " << root->nodeHeight <<  endl;
        // Search the right subtree to the end
        printInorder(root->right, target, count, foundID, print);
    }
}

void AVL::printPreorder(AVL::Node *root) {
    // Base case, we've reached the end go back
    if (root == nullptr){
        cout<< "";
    }
    else{
        // We are at the node, print out its data
        cout<< root->name << ",";
        // Search the left subtree to the end
        printPreorder(root->left);
        // Search the right subtree to the end
        printPreorder(root->right);
    }
}

void AVL::printPostorder(AVL::Node *root) {
    // Base case, we've reached the end go back
    if (root == nullptr){
        cout<< "";
    }
    else{
        // Search the left subtree to the end
        printPostorder(root->left);
        // Search the right subtree to the end
        printPostorder(root->right);
        // We are at the node, print out its data
        cout<< root->name << ",";
    }
}

void AVL::updateBalanceFactor(Node *root) {
    // Base case, we've reached the end go back
    if (root == nullptr){
        return;
    }
    else{
        // Make the balance factor the height of the left subtree minus the height of the right subtree, if there is no
        // right or left subtree use the current node's height in the formula
        root->balanceFactor = max(getMaxHeight(root->left), root->nodeHeight) - max(getMaxHeight(root->right), root->nodeHeight);
    }
}

int AVL::getMaxHeight(AVL::Node *root) {
    // There is no subtree, return 0
    if (root == nullptr){
        return 0;
    }
    // We've reached a leaf, this is one of the potential max heights
    else if (root->right == nullptr && root->left == nullptr){
        return root->nodeHeight;
    }
    else{
        // Keep searching the left and right subtrees until we reach leaves
        int left = getMaxHeight(root->left);
        int right = getMaxHeight(root->right);
        // Return the max value out of the two subtrees
        return max(left, right);
    }

}

AVL::Node* AVL::leftRotate(AVL::Node *root) {
    // Do the actual rotation
    Node* grandchild = root->right->left;
    Node* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    // Update the level of the nodes and their balance factors
    root->nodeHeight++;
    newParent->nodeHeight--;
    if (newParent->right != nullptr){
        newParent->right->nodeHeight--;
        updateBalanceFactor(newParent->right);
    }
    updateBalanceFactor(root);
    updateBalanceFactor(newParent);

    // Return the new parent node so the tree is pointing accurately
    return newParent;
}

AVL::Node* AVL::rightRotate(AVL::Node *root) {
    // Do the actual rotation
    Node* grandchild = root->left->right;
    Node* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;

    // Update the level of the nodes and their balance factors
    root->nodeHeight++;
    newParent->nodeHeight--;
    if (newParent->left != nullptr){
        newParent->left->nodeHeight--;
        updateBalanceFactor(newParent->left);
    }
    updateBalanceFactor(root);
    updateBalanceFactor(newParent);

    // Return the new parent node so the tree is pointing accurately
    return newParent;
}

void AVL::printLevelCount() {
    // Get the max height of the trees, that's equal to how many levels the tree has
    cout << getMaxHeight(head) << endl;
}

AVL::Node *AVL::search(int ID, Node* root, int &direction, bool print, bool found) {
    // Create a node pointer to return, this node will be the node right before the node we found
    Node* found_root = nullptr;
    // Call the recursive search until we find the node with matching data
    found_root = searchTransversal(ID, root, found, found_root, direction, print);
    // If nothing was found, print unsuccessful and return a null pointer
    if (!found){
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    // Otherwise return the node right before the one we care about
    else{
        return found_root;
    }
}

void AVL::search(string name, Node* root, bool found) {
    // Go through every node until we find the one we care about
    searchTransversal(name, root, found);
    // If nothing is found print as such
    if (!found){
        cout << "unsuccessful" << endl;
    }
}

AVL::Node* AVL::searchTransversal(int &ID, AVL::Node *root, bool &found, Node* found_root, int &direction, bool &print) {
    // If we've reached the end do nothing
    if (root == nullptr){
        cout << "";
    }
    // Otherwise check to see if we've found the wanted node
    else{
        // Check to see if the head is the one were looking for
        if(root->UFID == ID){
            found = true;
            direction = 2;
            return root;
        }
        // Check if the node to the right of our current one has our data
        if (root->right != nullptr && root->right->UFID == ID){
            // If it does, and the passed print parameter is true, we want to show the data so print it
            if (print){
                cout << root->right->name << endl;
            }
            // Change the passed found parameter and direction and then return the root before the one with data
            found = true;
            direction = 1;
            return root;
        }
        // Check if the node to the left of our current one has our data
        if (root->left != nullptr && root->left->UFID == ID){
            // If it does, and the passed print parameter is true, we want to show the data so print it
            if (print){
                cout << root->left->name << endl;
            }
            // Change the passed found parameter and direction and then return the root before the one with data
            found = true;
            direction = 0;
            return root;
        }
        // Continue searching in the left and right subtrees
        found_root = searchTransversal(ID, root->left, found, found_root, direction, print);
        found_root = searchTransversal(ID, root->right, found, found_root, direction, print);
    }
    // Return the found root, if there was none it's null pointer by default so no worries
    return found_root;
}

void AVL::searchTransversal(string &name, AVL::Node *root, bool &found) {
    // If we've reached the end do nothing
    if (root == nullptr){
        cout << "";
    }
    // Otherwise, check to see if the current node is the one we want
    else{
        // If it is, print the data and changed the passed found parameter
        if (root->name == name){
            cout << root->UFID << endl;
            found = true;
        }
        // Keep going through the whole tree, starting with left and then right subtrees
        searchTransversal(name, root->left, found);
        searchTransversal(name, root->right, found);
    }
}

void AVL::remove(int ID) {
    // Initialize a direction variable to pass as a parameter
    int direction = 0;
    // Find the node right before the one we want to delete
    Node* node_to_remove = search(ID, head, direction, false);
    // If the node we want to get rid of is the head, we gotta approach this differently
    if (node_to_remove == head && direction == 2){
        head = removeHelper(node_to_remove, direction);
    }
    // Otherwise, if there is a node to delete
    else if (node_to_remove != nullptr) {
        // Check whether we want to delete the node on the left or the right
        if (direction == 0){
            // Set the pointer of the node before to the newly returned subtree after deletion
            node_to_remove->left = removeHelper(node_to_remove, direction);
        }
        else {
            // Set the pointer of the node before to the newly returned subtree after deletion
            node_to_remove->right = removeHelper(node_to_remove, direction);
        }

    }
    // If there is no node to delete
    else {
        cout << "unsuccessful" << endl;
    }
}

AVL::Node *AVL::removeHelper(AVL::Node *node_to_remove, int &direction) {
    // Initialize a pointer we want the rest of the tree to point to after deletion
    Node* newParent = nullptr;

    // If the node to delete is on the left
    if (direction == 0){
        // Travel to that node
        node_to_remove = node_to_remove->left;
    }
    // If the node to delete is on the right
    else if (direction == 1){
        // Travel to that node
        node_to_remove = node_to_remove->right;
    }
    // Otherwise, the node is the head so do nothing


    // If the node we want to delete is a leaf node
    if (node_to_remove->left == nullptr && node_to_remove->right == nullptr){
        // Simply delete the node and return a null pointer to point to
        delete node_to_remove;
        cout << "successful" << endl;
        return nullptr;
    }
    // If the node has at least one child
    else if (node_to_remove->left == nullptr || node_to_remove->right == nullptr){
        // If the node has a child on the left
        if (node_to_remove->left != nullptr){
            // Set the return pointer to what it was pointing at and decrease the height
            newParent = node_to_remove->left;
            newParent->nodeHeight--;
            // Delete the node
            delete node_to_remove;
            cout << "successful" << endl;
        }
        // If the node has a child on the right
        else{
            // Set the return pointer to what it was pointing at and decrease the height
            newParent = node_to_remove->right;
            newParent->nodeHeight--;
            // Delete the node
            delete node_to_remove;
            cout << "successful" << endl;
        }
    }
    // The node has two children
    else{
        // Find the inorder successor to replace the node to be removed
        newParent = getSuccessor(node_to_remove->right, node_to_remove->UFID);
        // The left of the new parent is what is to the left of the node to be deleted
        newParent->left = node_to_remove->left;
        // If for whatever reason the node to the immediate right isn't the successor (Insertion after deletion for ex)
        if (node_to_remove->right != newParent){
            // Set the right of the new parent to the right of the node to be deleted
            newParent->right = node_to_remove->right;
        }
        // Change the heights of the nodes
        newParent->nodeHeight = node_to_remove->nodeHeight;
        // Delete the node
        delete node_to_remove;
        cout << "successful" << endl;
    }
    // Return the return pointer so that the tree connects to the modified subtree after deletion
    return newParent;
}

AVL::Node *AVL::getSuccessor(AVL::Node *root, int &currentMin) {
    // There is no subtree, return
    if (root == nullptr){
        return nullptr;
    }
        // We've reached a leaf, this is one of the potential successors
    else if (root->right == nullptr && root->left == nullptr){
        // Get the smallest value
        currentMin = min(currentMin, root->UFID);
        return root;
    }
    else{
        // Keep searching the left and right subtrees until we reach leaves
        getMaxHeight(root->left);
        getMaxHeight(root->right);
    }
    return nullptr;
}

void AVL::removeInorder(int nth) {
    int foundID = 0;
    int count = -1;
    printInorder(head, nth, count, foundID, false);
    if (foundID != 0) {
        remove(foundID);
    }
    else{
        cout << "unsuccessful" << endl;
    }
}
