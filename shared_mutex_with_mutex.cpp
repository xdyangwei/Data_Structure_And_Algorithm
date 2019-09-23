//
// Created by 杨炜 on 2019/9/23.
//

#include "shared_mutex_with_mutex.h"
void shared_mutex_with_mutex::read_lock() {
    protect_mutex.Lock();
    if(!read_count)
        work_mutex.Lock();
    read_count++;
    protect_mutex.Unlock();
}

void shared_mutex_with_mutex::read_unlock() {
    protect_mutex.Lock();
    read_count--;
    if(!read_count)
        work_mutex.Unlock();
    protect_mutex.Unlock();
}

void shared_mutex_with_mutex::write_lock() {
    work_mutex.Lock();
}

void shared_mutex_with_mutex::write_unlock() {
    work_mutex.Unlock();
}
