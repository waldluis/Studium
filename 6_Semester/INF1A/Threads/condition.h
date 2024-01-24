#if !defined __CONDITION_H
#define      __CONDITION_H

#include <pthread.h>

// See http://publib.boulder.ibm.com/iseries/v5r2/ic2924/info/apis/users_76.htm

class Condition
{
private:
    pthread_mutex_t mx;
    pthread_cond_t cnd;
    int flag;

public:
    explicit Condition()
    {
        pthread_mutex_init(&mx, 0);
        pthread_cond_init(&cnd, 0);
        flag = 0;
    }

    ~Condition()
    {
        // fails if locked or refd (e.g. by pthread_cond_wait()):
        pthread_mutex_destroy(&mx);
        // fails if someone is waiting on cnd:
        pthread_cond_destroy(&cnd);
    }

    void signal()
    {
        pthread_mutex_lock(&mx);
        flag = 1;
        pthread_cond_signal(&cnd);
        pthread_mutex_unlock(&mx);
    }

    void wait()
    {
        pthread_mutex_lock(&mx);
        while ( !flag )  pthread_cond_wait(&cnd, &mx);
        flag = 0;
        pthread_mutex_unlock(&mx);
    }
};
//-------------------------------------

#endif // !defined __CONDITION_H
