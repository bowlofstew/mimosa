/* Required for CPU_ALLOC(), ... */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <unistd.h>
#include <sched.h>

#include <cassert>
#include <vector>
#include <memory>

#include "cpu-count.hh"
#include "cpu-foreach.hh"
#include "thread.hh"

namespace mimosa
{
  void cpuForeach(const std::function<void ()>& cb)
  {
    std::vector<std::unique_ptr<Thread> > threads;
    int nproc = cpuCount();
    threads.resize(nproc);

    for (int i = 0; i < nproc; ++i)
    {
      threads[i].reset(new Thread([i, nproc, &cb] {
#ifdef HAS_SCHED_SETAFFINITY
            cpu_set_t * set = CPU_ALLOC(nproc);
            assert(set);
            CPU_ZERO_S(nproc, set);
            CPU_SET(i, set);

            sched_setaffinity(0, CPU_ALLOC_SIZE(nproc), set);
#endif /* HAS_SCHED_SETAFFINITY */

            try {
              cb();
            } catch (...) {
            }
#ifdef __linux__
            CPU_FREE(set);
#endif
          }));
      threads[i]->start();
    }

    for (int i = 0; i < nproc; ++i)
      threads[i]->join();
  }
}
