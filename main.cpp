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

        node(node*Node){//构建节点拷贝函数
            this->left=Node->left;
            this->right=Node->right;
            this->key=Node->key;
            this->value=Node->value;
        }

    };
    node*root;//root指向二叉树的根节点
    int count;//计数二叉树中的节点数

    node*insert(node*root,Key key,Value value){//root为开始搜索插入的起始根地址
        //
        if(root== nullptr){//如果查找的根地址为空
            count++;//插入新节点
            return new node(key ,value);//构造一个新节点，并返回
        }
        if(root->key==key){//覆盖节点
            root->value=value;
        }
        else key < root->key ? (root->left=insert(root->left, key, value)) : (root->right=insert(root->right, key, value));
        //进行节点连接操作
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
            return   leftnode;//返回上一级做连接使用
        }
        rootnode->right=removemax(rootnode->right);//连接被脱离的子树
        return rootnode;//返回当前节点的地址
    }
    // 返回以node为根的二分搜索树的最小键值所在的节点
    node* minmum(node* node){
        if( node->left == NULL )
            return node;

        return minmum(node->left);
    }

    // 返回以node为根的二分搜索树的最大键值所在的节点
    node* maximum(node* node){
        if( node->right == NULL )
            return node;

        return maximum(node->right);
    }


    /*
 * 删除以node为根的二叉树中的Key为key的节点
 * 并且返回新二叉树的根地址
 */
    node* remove(node*Node,Key key){
        if(Node==NULL){//如果树为空的话
            return NULL;//返回空值
        }
        else if(Node->key==key){//此时找到了需要被删除的节点

            if(Node->left==NULL){//待删除节点的左子树为空的话,右子树为空或者不为空都不影响
                node*rightnode=Node->right;//把右子树的根地址保存下来
                delete Node;//节点此时可以被删除了
                count--;//更新计数器
                return rightnode;//右子树为空的话，返回NULL，不为空的话，返回右子树的根节点
            }
            else if(Node->right==NULL){//此时待删除节点的右子树为空的话,左子树为空或者不为空都不影响
                node*leftnode=Node->left;//记录左子树的根地址，可能为空也可能为一个值，但不影响
                delete Node;//此时可以删除节点
                count--;//更新计数器
                return leftnode;//左子树为空的话，返回NULL，不为空的话，返回左子树的根节点
            }
            else{//此时待删除节点的左右子树均不为空的话
                //替换节点可以是该节点右子树中的最小值或者左子树的最大值，这里我们选右子树中的最小值作为替换
                node*replacenode=new node(minmum(Node->right)) ;//复制待删除节点右子树的最小节点作为替换节点
                count++;//增加计数器
                replacenode->right=removemin(Node->right);//删除待删节点的右子树的最小值并把新树的根地址再重新赋值给替代
                //节点的右子树
                replacenode->left=Node->left;//替代节点的左子树就是原来节点的左子树
                delete Node;//替代节点的左右子树都已经更新完毕了，可以删除了
                count--;//更新计数器
                return replacenode;//返回替代节点的地址即新树的根节点地址给上一层连接用
            }
        }
    }





public:
    BST(){
        root=NULL;
        count=0;
    }

    ~BST(){//利用后序遍历先删除孩子节点再删除根节点来删除一棵二叉树
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
        queue<node*> duilie;//构造一个存放node*类型的队列
        if(root!=NULL){//必须存在二叉树才能够进行层序遍历
            duilie.push(root);//先把根节点入队作为开始
            while (!duilie.empty()){
                    node*node=duilie.front();//取出队列的首元素进行访问操作
                    cout<<node->key<<' ';
                    if(node->left!=NULL){//被访问的节点有左孩子，也一起让其加入队列中
                        duilie.push(node->left);
                    }
                    if(node->right!=NULL){//被访问的节点有右孩子，也一起让其加入队列中
                        duilie.push(node->right);
                    }
                    duilie.pop();//队列首元素被访问完毕，其所有的孩子节点也入队完毕，可以出队


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
    Key minmum(){
        assert( count != 0 );
        node* minNode = minmum( root );
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

    void remove(Key key){
        root=remove(root,key);
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
    cout<<endl<<"delete the 3"<<endl;
    a.remove(3);
    a.leverorder();




  


    return 0;
}