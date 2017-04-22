//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_BSTREE_H
#define DSALGLIB_BSTREE_H

#include "bstree.h"
namespace dsa
{
    template<class type>
    class bstree
    {
        private:
            struct bstnode
            {

                bstnode   *left,*right;
                type    data;
                bstnode()
                {
                    left = nullptr;
                    right= nullptr;
                }
                bstnode(type param)
                {
                    left = nullptr;
                    right= nullptr;
                    data = param;
                }
            };

            /*
            Function: creates bstnode of type type
            Pre: param of type type to create bstnode
            Post: bstnode created
            */
            bstnode * create_bstnode(type param)
            {
                bstnode *temp = new bstnode(param);
                return temp;
            }

            bstnode *root;
            long long int count;

            bstnode * _find_min(bstnode * temp)
            {
                if(temp==nullptr)          return nullptr;
                if(temp->left==nullptr)    return temp;
                return _find_min(temp->left);
            }

            bstnode * _find_max(bstnode * temp)
            {
                if(temp==nullptr)          return nullptr;
                if(temp->right==nullptr)   return temp;
                return _find_max(temp->right);
            }

            bool _insert(bstnode *troot,bstnode *temp)
            {

                if(temp->data < troot->data)
                    if(troot->left==nullptr)
                        troot->left=temp;
                    else
                        return  _insert(troot->left,temp);
                else
                if(troot->right==nullptr)
                    troot->right=temp;
                else
                    return  _insert(troot->right,temp);

                return true;

            }

            bstnode * _remove(bstnode *troot,type param)
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
                    bstnode *temp = troot;
                    troot = ( troot->left != nullptr ) ? troot->left : troot->right;
                    delete temp;  count--;
                }
                return troot;
            }

            void _clear(bstnode *temp)
            {
                if(temp==nullptr) return;
                _clear(temp->left);
                _clear(temp->right);
                remove(temp->data);
            }

            void _inorder(bstnode *temp,void (fun)(type obj))
            {
                if(temp==nullptr) return;

                _inorder(temp->left,fun);
                fun(temp->data);
                _inorder(temp->right,fun);
            }

            void _preorder(bstnode *temp,void (fun)(type obj))
            {
                if(temp==nullptr) return;

                fun(temp->data);
                _preorder(temp->left,fun);
                _preorder(temp->right,fun);

            }

            void _postorder(bstnode *temp,void (fun)(type obj))
            {
                if(temp==nullptr) return;

                _postorder(temp->left,fun);
                _postorder(temp->right,fun);
                fun(temp->data);
            }

            void _levelorder(void (fun) (type obj))
            {
                queue<bstnode * > q;
                bstnode *temp;
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

            long long int _height(bstnode *temp)
            {

                if(temp==nullptr)  return -1;
                return maxof(_height(temp->left),_height(temp->right))+1;
            }

            bstnode * _search(bstnode *temp,type val)
            {
                if(temp==nullptr) return nullptr;

                if(val<temp->data) return _search(temp->left,val);
                else if(temp->data<val) return _search(temp->right,val);
                else return temp;

            }

        public:

            bstree()
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
                bstnode *temp = create_bstnode(param);

                if(root==nullptr)
                    root=temp;
                else
                    _insert(root,temp);

                count++;
                return true;

            }

            bool remove(type param)
            {
                long long int temp=count;
                root=_remove(root,param);
                if(count<temp)
                    return true;
                else
                    return false;
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

            void levelorder(void (fun) (type obj))
            {
                _levelorder(fun);
            }

            bool search(type val)
            {
                if(_search(root,val)!=nullptr)
                    return true;
                else
                    return false;
            }

    };
}


#endif //DSALGLIB_BSTREE_H
