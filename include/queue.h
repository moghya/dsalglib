//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_QUEUE_H
#define DSALGLIB_QUEUE_H
namespace dsa
{



    template<class type>
    class queue
    {
        private:
            struct qnode
            {
                type data;
                qnode *next;

                qnode()
                {
                    next = nullptr;
                }

                qnode(type param)
                {

                    data = param;
                    next = nullptr;
                }
            };
            qnode *front,*rear;
            long long int count;

            /*
                Function: creates qnode of type type
                Pre: param of type type to create qnode
                Post: qnode created
             */
            qnode* create_qnode(type param)
            {
                qnode *temp = new qnode(param);
                return temp;
            }

        public:
            queue()
            {
                front = nullptr;
                rear = nullptr;
                count = 0;
            }

            /*
             * Function: enqueues element in queue at rear
             * Pre: param element of type type
             * Post: element added
             */
            type enqueue(type param)
            {
                qnode *temp = create_qnode(param);
                if(count==0)
                {
                    front = temp;
                    rear  = temp;
                    front->next = rear;
                }
                else
                {
                    rear->next = temp;
                    rear = temp;

                }
                count++;
                return param;
            }

            /*
             * Function: removes element at front
             * Pre: none
             * Post: element removed
             */
            type dequeue()
            {
                type param;
                qnode *temp;
                if(count>0)
                {
                    if(count==1)
                    {
                        param = front->data;
                        delete front;
                        front = nullptr;
                        rear = nullptr;

                    }
                    else
                    {
                        param = front -> data;
                        temp = front -> next;
                        delete front;
                        front = temp;
                    }
                    count--;
                    return param;
                }
                else
                {
                    return param;
                }
            }

            /*
             * Function:gives value of front element
             * Pre: none
             * Post: front value returned
             */
            type front_element()
            {
                type param;
                if(count>0)
                {
                    param = front->data;
                }

                return param;
            }

            /*
             * Function:gives value of front element
             * Pre: none
             * Post: front value returned
             */
            type rear_element()
            {
                type param;
                if(count>0)
                {
                    param = rear->data;
                }

                return param;
            }

            /*
             * Function:'=' operator overloaded for copyin one queue vals into another
             * Pre: none
             * Post: copied
             */
            void operator=(queue<type> from)
            {
                clear();
                if(from.size()>0)
                {
                    qnode *temp= from.front;
                    while(temp!=from.rear)
                    {
                        enqueue(temp->data);
                        temp=temp->next;
                    }
                    enqueue(temp->data);
                }
                return;
            }

            /*
             * Function:gives size of queue
             * Pre: none
             * Post: front value returned
             */
            long long int size()
            {
                return count;
            }


            /*
             * Function: checks if empty
             * Pre: none
             * Post: true if isempty else false
             */
            bool isempty()
            {
                if(count==0)
                    return true;
                else
                    return false;
            }

            /*
             * Function: Removes all elements from queue
             * Pre: none
             * Post: queue empty
             */
            void clear()
            {
                while(count!=0)
                {
                    dequeue();
                }
            }
    };
}
#endif //DSALGLIB_QUEUE_H
