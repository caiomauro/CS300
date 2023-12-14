//CS300 Project 2 by Caio Mauro

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//Menu
void DisplayMenu()
{
    cout << "1. Load Courses" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Find Course Info" << endl;
    cout << "9. Quit" << endl
         << endl;
    cout << "Please input an option from the menu: ";
}

// Coure structure
struct Course
{
    string courseId;
    string courseName;
    vector<string> preRequisite;
};

// Node structure
struct Node
{
    Course course;
    Node *left;
    Node *right;

    Node()
    {
        left = nullptr;
        right = nullptr;
    }
    
    Node(Course aCourse) : course(aCourse), left(nullptr), right(nullptr) {}
};

// Binary tree class
class BinarySearchTree
{

private:
    void Destruct(Node *node);

public:
    Node *root;
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(BinarySearchTree *tree, Node *node);
    void Search(string courseId);
    void PrintCourse(Node *node);
};

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
    Destruct(root);
}

// Destruct method
void BinarySearchTree::Destruct(Node *node)
{
    if (node != nullptr)
    {
        Destruct(node->left);
        node->left = nullptr;
        Destruct(node->right);
        node->right = nullptr;
        delete node;
    }
}

// Search method
void BinarySearchTree::Search(string courseId)
{
    Node *currentNode = root;

    while (currentNode != nullptr)
    {
        // logic to find node
        if (currentNode->course.courseId == courseId)
        {
            cout << currentNode->course.courseId << ", ";
            cout << currentNode->course.courseName;
            cout << endl;
            cout << "Prerequisites: ";
            // loop through prerequisites
            for (vector<string>::iterator it = currentNode->course.preRequisite.begin(); it != currentNode->course.preRequisite.end(); ++it)
            {
                if (it == --currentNode->course.preRequisite.end())
                {
                    cout << *it << endl;
                }
                else
                {
                    cout << *it << ", ";
                }
            }

            return;
        }
        // left pointer check
        else if (courseId < currentNode->course.courseId)
        {

            if (currentNode->left != nullptr)
            {
                currentNode = currentNode->left;
            }
        }
        // right pointer check
        else
        {

            currentNode = currentNode->right;
        }
    }
    // Case for course not found
    cout << "Course " << courseId << "not in list. " << endl;
    return;
}

// Insert method
void BinarySearchTree::Insert(BinarySearchTree *tree, Node *node)
{

    if (tree->root == nullptr)
    {
        tree->root = node;
    }
    else
    {
        Node *curr = tree->root;
        while (curr != nullptr)
        {

            if (node->course.courseId < curr->course.courseId)
            {
                if (curr->left == nullptr)
                {
                    curr->left = node;
                    curr = nullptr;
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {

                if (curr->right == nullptr)
                {
                    curr->right = node;
                    curr = nullptr;
                }
                else
                {
                    curr = curr->right;
                }
            }
        }
    }
}

// Print method
void BinarySearchTree::PrintCourse(Node *node)
{

    // Check if tree is empty
    if (node == nullptr)
    {
        return;
    }

    // Recursive method to print each course
    PrintCourse(node->left);
    cout << node->course.courseId << ", ";
    cout << node->course.courseName << endl;
    PrintCourse(node->right);
}

// Read CSV and put into tree
void loadCourse(string filename, BinarySearchTree *bst)
{
    ifstream file(filename);
    // Opens file
    if (file.is_open())
    {
        cout << "File loaded." << endl;

        int num;
        string line;
        string word;

        while (getline(file, line))
        {

            num = 0;
            Node *node = new Node();
            stringstream str(line);

            while (num < 2)
            {
                getline(str, word, ',');
                if (num == 0)
                {
                    node->course.courseId = word;
                }
                else
                {
                    node->course.courseName = word;
                }
                num++;
            }
            while (getline(str, word, ','))
            {
                node->course.preRequisite.push_back(word);
            }

            bst->Insert(bst, node);
        }
    }
    // Case if file is not found
    else
    {
        cout << "Could not load file. " << endl;
        return;
    }
}

int main()
{

    BinarySearchTree *bst = new BinarySearchTree();

    string fileChoice;
    string courseChoice;

    int userInput = 0;

    cout << "CS300 Project 2 by Caio Mauro" << endl
         << endl;
    while (userInput != 9)
    {
        DisplayMenu();
        cin >> userInput;

        // Switch statement to handle user inputs
        switch (userInput)
        {
        case 1:
            cout << endl;
            cout << "Please input the filename to load: ";
            cin >> fileChoice;
            loadCourse(fileChoice, bst);
            cout << endl;
            break;
        case 2:
            cout << endl;
            cout << "Course ID | Course Name" << endl;
            bst->PrintCourse(bst->root);
            cout << endl;
            break;
        case 3:
            cout << endl;
            cout << "Which course would you like to find:  ";
            cin >> courseChoice;
            cout << endl;
            std::transform(courseChoice.begin(), courseChoice.end(), courseChoice.begin(), ::toupper);
            bst->Search(courseChoice);
            cout << endl;
            break;
        case 9:
            cout << "Quit Successfully" << endl;
            break;
        default:
            cout << userInput << "Unrecognized command" << endl
                 << endl;
            break;
        }
    }
}
