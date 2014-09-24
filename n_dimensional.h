#ifndef N_DIMENSIONAL_H
#define N_DIMENSIONAL_H
    #include <cstdarg>

    #ifndef NULL
        #define NULL 0
    #endif

    template <typename T, int D>
    class Node{
        public:
            typedef T val;
            typedef T& ref;
            typedef T const& const_ref;
            typedef T* ptr;
            typedef T const* const_ptr;

            // Constructor
            Node(val newvalue = 0) : value(newvalue){
                for (int i = 0; i < D; ++i){
                    _next[i] = NULL;
                }
            }

            void add(int dimension, val value = 0){
                _next[dimension] = new Node(value);
            }

            Node* next(int dimension){
                return _next[dimension];
            }

            val value;
        private:
            Node* _next[D];
    };

    template <typename T, int D>
    class NDimensionalSLL{
        // private:
            typedef Node<T, D> node_type;
            typedef node_type* node_ptr;
            node_ptr head;
        public:
            typedef typename node_type::val val;
            typedef typename node_type::ref ref;
            typedef typename node_type::const_ref const_ref;
            typedef typename node_type::ptr ptr;
            typedef typename node_type::const_ptr const_ptr;

            NDimensionalSLL() : head(new node_type){}
            /*
            node_ptr fill(T value, ...){
                int dimension[D];

                va_list vl;
                va_start(vl, value);
                    for (int i = 0; i < D; ++i){
                        dimension[i] = va_arg(vl, int);
                    }
                va_end(vl);

                for (int i = 0; i < D; ++i){
                    for (int i = 0; i < D; ++i){

                        node_ptr target = head;
                    }
                }

            }
            */
            node_ptr fill_short_from(T value, bool all, node_ptr start, ...){
                int dimension[D];

                va_list vl;
                va_start(vl, start);
                    for (int i = 0; i < D; ++i){
                        dimension[i] = va_arg(vl, int);
                    }
                va_end(vl);

                for (int i = 0; i < D; ++i){
                    start = fill_1d_from((all) ? value : 0, all, start, i, dimension[i]);
                }
                start->value = value;
                return start;
            }
            node_ptr fill_1d_from( T value, bool all, node_ptr start, int dimension, int distance){
                for (int i = 0; i < distance; ++i){
                    if (all || !start->next(dimension)){
                        start->add(dimension, (all) ? value : 0);
                        start = start->next(dimension);
                    }
                }
                start->value = value;
                return start;
            }
            node_ptr get(int first, ...){
                int dimension[D];

                va_list vl;
                va_start(vl, first);
                    // Hack for no first arg
                    dimension[0] = first;
                    for (int i = 1; i < D; ++i){
                        dimension[i] = va_arg(vl, int);
                    }
                va_end(vl);
                
                node_ptr target = head;
                bool done = false;
                int coord_counter[D] = {0};

                while (!done){
                    for (int i = 0; i < D; ++i){
                        if (coord_counter[i] != dimension[i]){
                            if (target->next(i)){
                                target = target->next(i);
                                ++coord_counter[i];
                                break;
                            }else if(i == (D - 1)){
                                throw "Target does not exist!";
                            }
                        }else if(i == (D - 1)){
                            done = true;
                        }
                    }
                }
                return target;
            }
            node_ptr get_direct(int first, ...){
                int dimension[D];

                va_list vl;
                va_start(vl, first);
                    // Hack for no first arg
                    dimension[0] = first;
                    for (int i = 1; i < D; ++i){
                        dimension[i] = va_arg(vl, int);
                    }
                va_end(vl);

                node_ptr target = head;
                for (int i = 0; i < D; ++i){
                    for (int j = 0; j < dimension[i]; ++j){
                        if (target->next(i)){
                            target = target->next(i);
                        }else{
                            throw "Target does not exist!";
                        }
                    }
                }
                return target;
            }
            /*
            void set(int value, ...){
                int dimension[D];

                va_list vl;
                va_start(vl, value);
                    for (int i = 0; i < D; ++i){
                        dimension[i] = va_arg(vl, int);
                    }
                va_end(vl);

                node_ptr target = head;
                for (int i = 0; i < D; ++i){
                    for (int j = 0; j < dimension[i]; ++j){
                        if (target->next(i)){
                            target = target->next(i);
                        }else{
                            throw "Target does not exist!";
                        }
                    }
                }
                target->value = value;
            }
            */
    };
#endif
