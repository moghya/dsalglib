//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_AVLTREE_H
#define DSALGLIB_AVLTREE_H

#include "queue.h"

namespace dsa
{
    template<class type>
    class avltree
    {
        private:
            static const long long int IF=1;
            struct avltnode
            {

                avltnode   *left,*right;
                type        data;
                long long int ht;


                avltnode()
                {
                    ht=-1;
                    left = nullptr;
                    right= nullptr;
                }

                avltnode(type param)
                {
                    ht=-1;
                    left = nullptr;
                    right= nullptr;
                    data = param;
                }
            };

            avltnode *root;
            long long int count;

            avltnode * create_avltnode(type param)
            {
               avltnode *temp = new avltnode(param);
               return temp;
            }

            long long int _height(avltnode *troot)
            {
                if(troot==nullptr)
                    return -1;
                else
                    return troot->ht;
            }

            void _rotateR(avltnode * &troot)
            {
                avltnode *temp;
                temp = troot->left;
                troot->left = temp->right;
                temp->right = troot;
                troot->ht = maxof( _height( troot->left ), _height( troot->right ) ) + 1;
                temp->ht = maxof( _height( temp->left ), troot->ht ) + 1;
                troot = temp;
            }

            void  _rotateL(avltnode * &troot)
            {
                avltnode *temp;
                temp = troot->right;
                troot->right = temp->left;
                temp->left = troot;
                troot->ht = maxof( _height( troot->left ),_height( troot->right ) ) + 1;
                temp->ht = maxof(troot->ht,_height( temp->right )) + 1;
                troot = temp;
            }

            void  _drotateR(avltnode * &troot)
            {
                _rotateL(troot->left);
                _rotateR(troot);
            }

            void  _drotateL(avltnode * &troot)
            {
                _rotateR(troot->right);
                _rotateL(troot);
            }

            void  _balance(avltnode * &troot)
            {
                if(troot==nullptr) return;
                long long int lh=_height(troot->left),rh=_height(troot->right);

                if(lh-rh>IF)
                {
                    long long int llh=_height(troot->left->left), lrh=_height(troot->left->right);
                    if(llh>=lrh)
                        _rotateR(troot);
                    else
                        _drotateR(troot);
                }
                else if(rh-lh>IF)
                {
                    long long int rlh=_height(troot->right->left), rrh=_height(troot->right->right);
                    if(rrh>=rlh)
                        _rotateL(troot);
                    else
                        _drotateL(troot);
                }

                lh = _height( troot->left );
                rh = _height( troot->right );
                troot->ht= maxof( lh, rh ) + 1;

            }

            avltnode * _insert(avltnode *troot,avltnode *temp)
            {

                if(troot==nullptr)
                    troot=temp;
                else if(temp->data < troot->data)
                        troot->left = _insert(troot->left,temp);
                     else
                        troot->right = _insert(troot->right,temp);
               _balance(troot);
               return troot;
            }

            avltnode * _find_min(avltnode * temp)
            {
                if(temp==nullptr)          return nullptr;
                if(temp->left==nullptr)    return temp;
                return _find_min(temp->left);
            }

            avltnode * _find_max(avltnode * temp)
            {
                if(temp==nullptr)          return nullptr;
                if(temp->right==nullptr)   return temp;
                return _find_max(temp->right);
            }

            avltnode * _remove(avltnode *troot,type param)
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
                       avltnode *temp = troot;
                       troot = ( troot->left != nullptr ) ? troot->left : troot->right;
                       delete temp;  count--;
                    }

                _balance(troot);
                return troot;
            }

            void _preorder(avltnode *temp,void (fun)(type obj))
            {
                if(temp==nullptr) return;

                fun(temp->data);
                _preorder(temp->left,fun);
                _preorder(temp->right,fun);

            }

            void _postorder(avltnode *temp,void (fun)(type obj))
            {
                if(temp==nullptr) return;

                _postorder(temp->left,fun);
                _postorder(temp->right,fun);
                fun(temp->data);
            }

            void _inorder(avltnode *temp,void (fun)(type obj))
            {
                if(temp==nullptr) return;

                _inorder(temp->left,fun);
                fun(temp->data);
                _inorder(temp->right,fun);
            }

            void _levelorder(void (fun) (type obj))
            {
                queue<avltnode * > q;

                avltnode *temp;
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

            avltnode * _search(avltnode *temp,type val)
            {
                if(temp==nullptr) return nullptr;

                if(val<temp->data) return _search(temp->left,val);
                else if(temp->data<val) return _search(temp->right,val);
                else return temp;

            }

            void _clear(avltnode *temp)
            {
                if(temp==nullptr) return;
                _clear(temp->left);
                _clear(temp->right);
                delete temp;
            }

        public:

            avltree()
            {
                root=nullptr;
                count=0;
            }

            bool insert(type param)
            {
                avltnode *temp = create_avltnode(param);
                root = _insert(root,temp);
                count++;
                return true;
            }

            bool remove(type param)
            {
                long long int temp = count;
                root = _remove(root,param);
                if(count<temp)
                    return true;
                else
                    return false;
            }

            void preorder(void (fun)(type obj))
            {
               _preorder(root,fun);
            }

            void postorder(void (fun)(type obj))
            {
               _postorder(root,fun);
            }

            void inorder(void (fun)(type obj))
            {
               _inorder(root,fun);
            }

            void levelorder(void (fun) (type obj))
            {
                _levelorder(fun);
            }

            type find_min()
            {
                return _find_min(root)->data;
            }

            type find_max()
            {
                return _find_max(root)->data;
            }

            void clear()
            {
                _clear(root);
            }

            long long int size()
            {
                return count;
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

            type tree_root()
            {
                return root->data;
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
#endif //DSALGLIB_AVLTREE_H
