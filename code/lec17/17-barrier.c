// single use barrier
int remain = 8;

void barrier_wait() {
  p_mutex_lock(&m);
  remain --;
  if(remain == 0) {
    p_cond_broadcast(&cv);
  } else {
    while(remain > 0) {
      p_cond_wait( &cv, &m); // remember: unlock - sleep(block) -- lock m
    }
  }
  unlock(&m);
}

