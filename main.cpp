#include <iostream>
#include<queue>
#include <assert.h>
using namespace std;
template <typename Key,typename Value>
class BST{//构建二叉搜索树类
private:
    struct node{//构建节点结构
        Key key;
        Value value;
        node*left;//left指向左节点
        node*right;//right指向右节点

        node(Key key ,Value value){//初始化节点
            this->key=key;
            this->value=value;
            this->left= nullptr;
            this->right= nullptr;
        }

    };
    node*root;//root指向二叉树的根节点
    int count;//计数二叉树中的节点数

    node*insert(node*root,Key key,Value value){//root为开始搜索插入的起始根地址
        //
        if(root== nullptr){//如果查找的根地址为空
            count++;//插入新节点
            return new node(key ,value);
        }
        if(root->key==key){//覆盖节点
            root->value=value;
        }
        else key < root->key ? (root->left=insert(root->left, key, value)) : (root->right=insert(root->right, key, value));
        return root;//返回根地址
    }
    /*
     * 在以root为根的二叉树中查找Key为key的节点
     * 如果没有则返回false
     */
    bool contain(node*node,Key key){
    if(node== nullptr){
        return false;
    }
        if(node->key==key){
            return true;
        }
       else if(key<node->key){
            return contain(node->left,key);
        }
        else return contain(node->right,key);
    }
    /*
     * 返回键key对应的value值的地址
     * 如果不存在该key则返回NULL
     */
    Value*search(node*node,Key key){
        if(node==NULL){
            return NULL;
        }
        if(node->key==key){
            return &(node->value);
        }
        if(key<node->key){
            return search(node->left,key);
        }
        else{
            return search(node->right,key);
        }

    }
    //以前序遍历来遍历以root为根节点的二叉树
    void preorder(node*node){
        if (node!=NULL) {//切记一定不能遗忘if判定条件，否则遍历不会停止
            cout<<node->key<<' ';//前阶段
            preorder(node->left);//中阶段
            preorder(node->right);//后阶段
        }
    }
    //中序遍历以node为根的二叉树
    void inorder(node*node){
        if(node!=NULL) {//切记一定不能遗忘if判定条件，否则遍历不会停止
            inorder(node->left);
            cout << node->key << ' ';
            inorder(node->right);
        }

    }
    //以后序遍历的方式遍历以root为根的二叉树
    void postorder(node*node){
        if (node!=NULL) {//切记一定不能遗忘if判定条件，否则遍历不会停止
            postorder(node->left);
            postorder(node->right);
            cout<<node->key<<' ';
        }

    }
//删除以node为根的二叉树
    void deletetree(node*node){
        if(node!=NULL){//先利用根中包含了叶子信息的特点去先删除叶子节点
            deletetree(node->left);
            deletetree(node->right);
            delete node;//最后删除根节点
            count--;
        }
    }

    //删除rootnode为根的二叉树的最小值，并且把删除后的树的地址返回
    node*removemin(node*rootnode){
        if(rootnode->left==NULL){//遍历到了树中最左边的节点，也就是该树中最小的节点
            node*rightroot=rootnode->right;//把要删除的节点的右子树根节点的地址保存好
            delete rootnode;//需要先记录右子树地址在删除节点，否则先删除节点则丢失了右子树根节点的地址
            count--;
            return rightroot;//把右子树的根地址返回到上一层以供连接使用
        }
        rootnode->left=removemin(rootnode->left);//连接记录好的右子树的根地址，重组为父节点的左子树
        return rootnode;
    }

     // 删除以rootnode为根的二叉树的最大节点，并把新树的根节点返回

    node*removemax(node*rootnode){
        if(rootnode->right==NULL){//遍历到了树中最大节点的位置
            node*leftnode=rootnode->left;//保存住被删除节点左子树的根节点地址
            delete rootnode;//需要先记录左子树地址在删除节点，否则先删除节点则丢失了左子树根节点的地址
            count--;
            return leftnode;//返回上一级做连接使用
        }
        rootnode->right=removemax(rootnode->right);//连接被脱离的子树
        return rootnode;//返回当前节点的地址
    }
    // 返回以node为根的二分搜索树的最小键值所在的节点
    node* minimum(node* node){
        if( node->left == NULL )
            return node;

        return minimum(node->left);
    }

    // 返回以node为根的二分搜索树的最大键值所在的节点
    node* maximum(node* node){
        if( node->right == NULL )
            return node;

        return maximum(node->right);
    }





public:
    BST(){
        root=NULL;
        count=0;
    }

    ~BST(){
        deletetree();
    }
    int size(){//返回节点数量
        return count;
    }

    bool isempty(){//返回二叉树是否为空
        return count==0;
    }

    void insert(Key key,Value value){//对二叉树进行插入操作

        root=insert(root, key , value);

    }

    bool contain(Key key){
        return contain(root,key);
    }

    Value*search(Key key){
        return search(root,key);
    }

    void preorder(){
        preorder(root);
    }

    void inorder()
    {
        inorder(root);
    }

    void postorder(){
        postorder(root);
    }

    void leverorder(){
        queue<node*> duilie;
        if(root!=NULL){//必须存在二叉树才能够进行层序遍历
            duilie.push(root);
            while (!duilie.empty()){
                    node*node=duilie.front();
                    cout<<node->key<<' ';
                    if(node->left!=NULL){
                        duilie.push(node->left);
                    }
                    if(node->right!=NULL){
                        duilie.push(node->right);
                    }
                    duilie.pop();


            }
        }
    }

    void deletetree(){
        deletetree(root);
    }

    void removemin(){
        if(root!=NULL)
        root=removemin(root);//此处切记，一定要把新的root值重新赋值给root，否则若树根被删除的话，将会引发错误
    }

    // 寻找二分搜索树的最小的键值
    Key minimum(){
        assert( count != 0 );
        node* minNode = minimum( root );
        return minNode->key;
    }

    // 寻找二分搜索树的最大的键值
    Key maximum(){
        assert( count != 0 );
        node* maxNode = maximum(root);
        return maxNode->key;
    }
    //删除树中的最大节点
    void removemax(){
        root=removemax(root);
    }

  
};



int main()
{
    BST<int,int> a=BST<int,int>();

    a.insert(3,4);
    a.insert(1,4);
    a.insert(5,4);
    a.insert(2,4);
    a.leverorder();
    a.removemin();
    cout<<endl;
    cout<<"delete the min:"<<endl;
    a.leverorder();
    cout<<endl;
    a.removemax();
    cout<<"delete the max:"<<endl;
    a.leverorder();


  


    return 0;
}