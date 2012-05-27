#include <unistd.h>
#include <sched.h>

#include <cassert>
#include <vector>
#include <memory>

#include "cpu-foreach.hh"
#include "thread.hh"

namespace mimosa
{
  void cpuForeach(const std::function<void ()>& cb)
  {
    int nproc = sysconf(_SC_NPROCESSORS_ONLN);

    std::vector<std::unique_ptr<Thread> > threads;
    threads.resize(nproc);

    for (int i = 0; i < nproc; ++i)
    {
      threads[i].reset(new Thread([i, nproc, &cb] {
            cpu_set_t * set = CPU_ALLOC(nproc);
            assert(set);
            CPU_ZERO_S(nproc, set);
            CPU_SET(i, set);

            sched_setaffinity(0, CPU_ALLOC_SIZE(nproc), set);

            try {
              cb();
            } catch (...) {
            }

            CPU_FREE(set);
          }));
      threads[i]->start();
    }

    for (int i = 0; i < nproc; ++i)
      threads[i]->join();
  }
}