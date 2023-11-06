#include<bits/stdc++.h>
using namespace std;

struct node {
    int data;
    struct node *left , *right;
};


struct node *newnode(int data)
{
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left=temp->right= NULL;
    return temp;
}

struct node * insert(struct node *root, int data)
{
    if(root==NULL)
    return newnode(data);

    if(data<root->data)
    root->left=insert(root->left,data);
    else
    root->right=insert(root->right,data);

    return root;

}

struct node * search(struct node *root, int data)
{
    if(root==NULL)
    return 0;

    if(data==root->data)
    return root;

    if(data<root->data)
    return search(root->left,data);

    else
    return search(root->right,data);

}

void inorder(struct node * root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
}

int height(struct node* root){
        // code here 
        if(root==NULL)
        return 0;
        int left=height(root->left);
        int right=height(root->right);
        return max(1+left,1+right);
}

struct node * searchIter(struct node* root, int data){
    while(root!=NULL){
        if(data == root->data){
            return root;
        }
        else if(data<root->data){
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    return NULL;
}

int main ()
{
    struct node *root = NULL;
    root = insert(root, 10 );
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    insert(root, 2);
    int h= height(root);
    cout<<h-1<<"fuck you"<<endl;
    // inorder(root);
    struct node* req = searchIter(root,2);
    cout<<req->data<<" is the  element ";
}

