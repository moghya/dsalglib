//
// Created by moghya_s on 10/12/2016.
//

#ifndef DSALGLIB_LINKLIST_H
#define DSALGLIB_LINKLIST_H
namespace dsa
{
    template<class type>
    class linklist
    {
        private:
            struct lnode
            {

                lnode *prev;
                type data;
                lnode *next;

                lnode()
                {
                    prev = nullptr;
                    next= nullptr;
                }

                lnode(type param)
                {
                    prev = nullptr;
                    data = param;
                    next = nullptr;
                }
            };

            lnode* create_lnode(type param)
            {
                lnode *temp = new lnode(param);
                return temp;
            }

            lnode *start,*last;
            long long int count;

        public:
            linklist()
            {
                start = nullptr;
                last = nullptr ;
                count = 0;
            }

            /*
             * Function: checks if list is empty
             * Pre: none
             * Post: Returns True if list is empty else False
             */
            bool isempty()
            {
                if(count==0)
                    return true;
                else
                    return false;
            }

            /*
             * Function: Removes all lnodes and makes list empty
             * Pre: none
             * Post: none
             */
            void clear()
            {
                while(count!=0)
                {
                    pop_back();
                }
                return;
            }

            /*
             *Function:Returns size of the list
             *Pre: none
             *Post: returns size of list;
             */
            long long int size()
            {
                return count;
            }

            /*
             * Function: '=' operator overloaded for copying contents of one list into other
             * Pre: List to copy into
             * Post: Copied
             */
            void operator=(linklist<type> from)
            {
                clear();
                if(from.size()>0)
                {
                    lnode *temp= from.start;
                    while(temp!=from.last)
                    {
                        add_back(temp->data);
                        temp=temp->next;
                    }
                    add_back(temp->data);
                }
                return;
            }

            /*
             * Function: '[]' operator overloaded for element access
             * Pre: index of element to access
             * Post: returns data value of element at index
             */
            type &operator[](long long int index)
            {
                if(index>=0&&index<count)
                {
                    lnode *temp = start;
                    long long int counter = 0;
                    while(counter<index)
                    {
                        temp=temp->next;
                        counter++;
                    }
                    return temp->data;
                }
            }

            /*
             * Function: adds lnode into list at end
             * Pre: param of type type to add into list
             * Post: param added into list at the last
             */
            void add_back(type param)
            {

                lnode *temp = create_lnode(param);
                if(start == nullptr)
                {
                    temp->prev = nullptr;
                    start=temp;
                    last = temp;
                    last->next = start;
                    start->prev = last ;
                }
                else
                {
                    last->next = temp;
                    temp->prev = last;
                    temp->next = start;
                    last = temp;
                }
                count++;
            }

            /*
             * Function: adds lnode into list at front
             * Pre: param of type type to add into list
             * Post: param added into list at the front
             */
            void add_front(type param)
            {
                lnode *temp = create_lnode(param);
                if(start == nullptr)
                {
                    temp->prev = nullptr;
                    start=temp;
                    last = temp;
                    last->next = start;
                    start->prev = last ;
                }
                else
                {
                    temp->next = start;
                    start->prev = temp;
                    temp->prev = last;
                    last->next=temp;
                    start = temp;
                }
                count++;
            }

            /*
             * Function: deletes first lnode from list
             * Pre: none
             * Post: deletes first lnode
             */
            void pop_front()
            {

                if(count>0)
                {
                    lnode *temp = start,*another_temp;
                    if(count==1)
                    {
                        delete temp;
                        start = nullptr;
                        last = nullptr;
                        count--;
                        return ;
                    }
                    else
                    {
                        another_temp=temp->next;
                        delete temp;
                        another_temp->prev = last;
                        start = another_temp;
                        count--;
                        return ;
                    }
                }
                else
                {
                    return ;
                }

            }

            /*
             * Function: deletes last lnode from list
             * Pre: none
             * Post: deletes last lnode
             */
            void pop_back()
            {
                if(count>0)
                {
                    lnode *temp = last,*another_temp;
                    if(count==1)
                    {
                        delete temp;
                        start = nullptr;
                        last = nullptr;
                        count--;
                        return ;
                    }
                    else
                    {

                        another_temp=temp->prev;
                        another_temp->next = start;
                        last = another_temp;
                        delete temp;
                        count--;
                        return ;
                    }

                }
                else
                {
                    return ;
                }
            }

            long long int search(type svalue)
            {
                if(count>0)
                {
                    long long int i=0;
                    lnode *temp = start->next;
                    if(start->data==svalue) return 0;
                    if(last->data==svalue) return count-1;

                    while(temp!=last)
                    {
                        i++;
                        if(temp->data==svalue)
                            return i;

                        temp = temp->next;

                    }
                }
                return -1;
            }

            void remove(type rvalue)
            {

                if(count>0)
                {
                    lnode *temp = start->next,*another_temp=nullptr;
                    if(start->data==rvalue)
                    {
                        pop_front();
                        return ;
                    }
                    if(last->data==rvalue)
                    {
                        pop_back();
                        return ;
                    }
                    while(temp!=last)
                    {
                        if(temp->data==rvalue)
                        {
                            another_temp->next=temp->next;
                            delete temp;
                            return ;
                        }
                        another_temp = temp;
                        temp = temp->next;
                    }
                }

                return ;
            }

            /*
             * Function: deletes lnode from list
             * Pre: index of lnode to delete
             * Post: deletes lnode at index
             */
            void remove_at(long long int index)
            {

                if(index>=0&&index<count)
                {

                    if(index==0)
                        return pop_front();
                    if(index==count-1)
                        return pop_back();

                    lnode *temp = start,*another_temp;
                    long long int counter = 1;
                    while(counter<index)
                    {
                        temp=temp->next;
                        counter++;
                    }
                    another_temp=temp->next->next;
                    delete temp->next;
                    temp->next = another_temp;
                    another_temp->prev = temp;
                    count--;
                    return ;
                }
                else
                    return ;
            }

            void traverse(void (fun)(type obj))
            {
                long long int i;
                lnode *temp=start;
                for(i=0;i<count;i++)
                {
                    fun(temp->data);
                    temp = temp->next;
                }
            }
    };
}
#endif //DSALGLIB_LINKLIST_H
