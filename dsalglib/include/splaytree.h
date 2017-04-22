//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_SPLAYTREE_H
#define DSALGLIB_SPLAYTREE_H
//not working
namespace dsa
{

    template<class type>
    class splaytree
    {
    private:
        struct splaytnode
        {

            splaytnode   *left,*right;
            type    data;


            splaytnode()
            {
                left = nullptr;
                right= nullptr;
            }

            splaytnode(type param)
            {
                left = nullptr;
                right= nullptr;
                data = param;
            }
        };


        splaytnode* create_splaytnode(type param)
        {
            splaytnode *temp = new splaytnode(param);
            return temp;
        }

        splaytnode *root;
        long long int count;

        void _rotateR(splaytnode * &troot)
        {
            splaytnode *temp;
            temp = troot->left;
            troot->left = temp->right;
            temp->right = troot;
            troot = temp;
        }

        void  _rotateL(splaytnode * &troot)
        {
            splaytnode *temp;
            temp = troot->right;
            troot->right = temp->left;
            temp->left = troot;
            troot = temp;
        }

        void _splay(splaytnode * &troot, type param)
        {
            if (troot == nullptr ) return;
            int i=0;
            if (param < troot->data) i=-1;
            else if(troot->data < param) i=1;

            if(i == 0)       return ;

            if (i==-1)
            {

                if (troot->left == nullptr) return ;

                if ( param < troot->left->data )
                {
                    _splay(troot->left->left, param);
                    _rotateR(troot);
                }
                else if (troot->left->data < param)
                {

                    _splay(troot->left->right, param);

                    if (troot->left->right != nullptr)
                        _rotateL(troot->left);
                }

                if(troot->left !=nullptr) _rotateR(troot);	return;
            }
            else
            {
                if (troot->right == nullptr) return ;


                if (param < troot->right->data)
                {
                    _splay(troot->right->left, param);
                    if (troot->right->left != nullptr)  _rotateR(troot->right);
                }
                else if (troot->right->data < param)
                {
                    _splay(troot->right->right, param);
                    _rotateL(troot);
                }

                if(troot->right !=nullptr) _rotateL(troot);	return;
            }
        }

        splaytnode* _find_min(splaytnode* temp)
        {
            if(temp==nullptr)          return nullptr;
            if(temp->left==nullptr)    return temp;
            return _find_min(temp->left);
        }

        splaytnode* _find_max(splaytnode* temp)
        {
            if(temp==nullptr)          return nullptr;
            if(temp->right==nullptr)   return temp;
            return _find_max(temp->right);
        }

        bool _insert(splaytnode *temp)
        {

            _splay(root,temp->data);

            if(root->data < temp->data)
            {
                temp->left = root;
                root = temp;
            }
            else
            {
                temp->right = root;
                root = temp;
            }

            return true;

        }

        splaytnode* _remove(splaytnode *troot,type param)
        {

            if( troot == nullptr )             return troot;

            if( param < troot->data )       troot->left = _remove(troot->left,param);
            else if( troot->data < param )  troot->right =_remove(troot->right,param);
            else if(troot->left!=nullptr&&troot->right!=nullptr)
            {
                troot->data = _find_min(troot->right)->data;
                troot->right = _remove(troot->right,troot->data);
            }
            else
            {
                splaytnode *temp = troot;
                troot = ( troot->left != nullptr ) ? troot->left : troot->right;
                delete temp;  count--;
            }
            return troot;
        }

        void _clear(splaytnode *temp)
        {
            if(temp==nullptr) return;
            _clear(temp->left);
            _clear(temp->right);
            remove(temp->data);
        }

        void _inorder(splaytnode *temp,void (fun)(type obj))
        {
            if(temp==nullptr) return;

            _inorder(temp->left,fun);
            fun(temp->data);
            _inorder(temp->right,fun);
        }

        void _preorder(splaytnode *temp,void (fun)(type obj))
        {
            if(temp==nullptr) return;

            fun(temp->data);
            _preorder(temp->left,fun);
            _preorder(temp->right,fun);

        }

        void _postorder(splaytnode *temp,void (fun)(type obj))
        {
            if(temp==nullptr) return;

            _postorder(temp->left,fun);
            _postorder(temp->right,fun);
            fun(temp->data);
        }

        void _bfs(void (fun) (type obj))
        {
            queue<splaytnode *> q;
            splaytnode *temp;
            if(root!=nullptr)
            {
                q.enqueue(root);
                while(!q.isempty())
                {
                    temp=q.front_element();
                    fun(temp->data);
                    if(temp->left!=nullptr)      q.enqueue(temp->left);
                    if(temp->right!=nullptr)     q.enqueue(temp->right);
                    q.dequeue();
                }
            }
        }

        long long int _height(splaytnode *temp)
        {
            if(temp==nullptr)  return -1;
            return maxof(_height(temp->left),_height(temp->right))+1;
        }

        splaytnode* _search(splaytnode *temp,type val)
        {

        }

    public:

        splaytree()
        {
            root = nullptr;
            count=0;
        }

        type find_min()
        {
            return _find_min(root)->data;
        }

        type find_max()
        {
            return _find_max(root)->data;
        }

        bool insert(type param)
        {
            splaytnode *temp = create_splaytnode(param);

            if(root==nullptr)
                root=temp;
            else
                _insert(temp);

            count++;
            return true;

        }

        bool remove(type param)
        {

        }

        type tree_root()
        {
            return root->data;
        }

        long long int size()
        {
            return count;
        }

        void clear()
        {
            _clear(root);
        }

        long long int height()
        {
            return _height(root);
        }

        bool isempty()
        {
            if(count==0)
                return true;
            else
                return false;
        }

        void inorder(void (fun)(type obj))
        {
            _inorder(root,fun);
        }

        void preorder(void (fun)(type obj))
        {
            _preorder(root,fun);
        }

        void postorder(void (fun)(type obj))
        {
            _postorder(root,fun);
        }

        void bfs(void (fun) (type obj))
        {
            _bfs(fun);
        }

        bool search(type val)
        {

        }

    };
}
#endif //DSALGLIB_SPLAYTREE_H
