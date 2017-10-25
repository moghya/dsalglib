//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_STACK_H
#define DSALGLIB_STACK_H
namespace dsa {

    template<class type>
    class stack {
        private:

            struct snode {
                snode *prev;
                type data;
                snode *next;

                snode() {
                    prev = nullptr;
                    next = nullptr;
                }

                snode(type param) {
                    prev = nullptr;
                    data = param;
                    next = nullptr;
                }
            };
            snode *top;
            long long int count;

            /*
            Function: creates qnode of type type
            Pre: param of type type to create qnode
            Post: qnode created
             */
            snode* create_snode(type param) {
                snode *temp = new snode(param);
                return temp;
            }

        public:

            stack() {
                top = nullptr;
                count = 0;
            }

            /*
             * Function: Pushes element on stack
             * Pre: param element of type type
             * Post: element added
             */
            type push(type param) {
                snode *temp = create_snode(param);
                if (count == 0) {
                    top = temp;
                } else {
                    top->next = temp;
                    temp->prev = top;
                    top = temp;

                }
                count++;
                return top->data;
            }

            /*
             * Function: Pop element from stack
             * Pre: none
             * Post: element removed
             */
            type pop() {
                type param;
                if (count > 0) {
                    snode *temp = top->prev;
                    if (count == 1) {
                        param = top->data;
                        delete top;
                        top = nullptr;
                    } else {
                        param = top->data;
                        temp->next = nullptr;
                        delete top;
                        top = temp;
                    }
                    count--;
                }
                return param;
            }

            /*
             * Function: gives top element
             * Pre: none
             * Post: top element returned
             */
            type top_element() {
                type param;
                if (count > 0)
                    param = top->data;

                return param;
            }

            /*
             * Function: no of elements in stack
             * Pre: none
             * Post: size returned
             */
            long long int size() {
                return count;
            }

            /*
             * Function: checks if empty
             * Pre: none
             * Post: true if isempty else false
             */
            bool isempty() {
               
               return (count == 0);
            }

            /*
             * Function: Removes all elements from stack
             * Pre: none
             * Post: stack empty
             */
            void clear() {
                while (count != 0) {
                    pop();
                }
            }
    };
}
#endif //DSALGLIB_STACK_H
