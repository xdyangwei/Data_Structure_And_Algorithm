//
// Created by 杨炜 on 2019/9/23.
//

#ifndef DATA_STRUCTURE_AND_ALGORITHM_SHARED_MUTEX_WITH_MUTEX_H
#define DATA_STRUCTURE_AND_ALGORITHM_SHARED_MUTEX_WITH_MUTEX_H
class my_mutex{
public:
    void Lock();
    void Unlock();
};

class shared_mutex_with_mutex {
public:
    void read_lock();
    void read_unlock();
    void write_lock();
    void write_unlock();
private:
    my_mutex protect_mutex;
    my_mutex work_mutex;
    int read_count;
};


#endif //DATA_STRUCTURE_AND_ALGORITHM_SHARED_MUTEX_WITH_MUTEX_H
