/*********************************
 * author     : most khal
 * date       : Sat Jul 12 05:43:47 PM EEST 2025
 * desc       : scheduler that works certain template functions
 ********************************/
#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

// bring this file here before you make a repo for scheduler
//functions for tasks must be void

#include <string>
#include <functional>
#include <vector>
#include <tuple>
#include <thread>

template <typename... ARGS>
class scheduler
{
  public:
    scheduler();
    scheduler(float t);

    void add(std::function<void(ARGS...)>, ARGS...);
    void pop(std::function<void(ARGS...)>, ARGS...);
    void setWait(float w);
    void run();

    size_t size();

  private:
    float wait = 0;

    std::vector<std::function<void(ARGS...)>> tasks;
    std::vector<std::tuple<ARGS...>>          targs;
};

template <typename... ARGS>
scheduler<ARGS...>::scheduler(): wait(1)
{
}

template <typename... ARGS>
scheduler<ARGS...>::scheduler(float t): wait(t)
{
}

template <typename... ARGS>
void scheduler<ARGS...>::add(std::function<void(ARGS...)> f, ARGS... args)
{
  // std::cout << "adding task\n";
  tasks.emplace_back(f);
  targs.emplace_back(std::make_tuple(args...));
}

template <typename... ARGS>
void scheduler<ARGS...>::pop(std::function<void(ARGS...)> f, ARGS... args)
{
  tasks.pop_back();
  targs.pop_back();
}

template <typename... ARGS>
void scheduler<ARGS...>::setWait(float w)
{
  wait = w;
}

template <typename... ARGS>
void scheduler<ARGS...>::run()
{
  for(int i = 0; i < tasks.size(); ++i)
  {
    std::apply(tasks[i], targs[i]);
    std::this_thread::sleep_for(std::chrono::duration<float>(wait));
    //std::cout << "running task: " << i << '\n';
  }
}

template <typename... ARGS >
size_t scheduler<ARGS...>::size()
{
  return tasks.size();
}

#endif /* !SCHEDULE_HPP */
