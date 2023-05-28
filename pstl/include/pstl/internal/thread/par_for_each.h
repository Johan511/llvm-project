#include "executor.h"
#include <iterator>
#include <vector>
#include <thread>

namespace __pstl_thread_backend
{

template <typename _algorithm>
class __pstl_algorithm
{

  public:
    template <typename ExPolicy, typename Iter, typename... Args>
    auto
    operator()(ExPolicy&& exPolicy, Iter first, Iter sent, Args... args)
    {
        if (true /*std::random_access_iterator<Iter> && __pstl_algorithm::is_parallel_policy<ExPolicy>*/)
            static_cast<_algorithm*>(this)->parallel(first, sent, args...);
        else
            static_cast<_algorithm*>(this)->sequential(first, sent, args...);
    }
};
class __for_each : public __pstl_algorithm<__for_each>
{
  public:
    template <typename Iter>
    static std::vector<Iter>
    __for_each_partitioner(Iter first, Iter sent)
    {
        std::size_t numProcessingUnits = ThreadExecutor::get_num_exec_unit();
        std::size_t n = std::distance(first, sent);

        std::size_t chunkSize = n / numProcessingUnits;

        std::vector<Iter> paritions(n + 1);
        Iter iter = first;
        std::size_t i = 0;
        for (; i != n; i++)
        {
            paritions[i] = iter;
            std::advance(iter, chunkSize);
            paritions[i + 1] = iter;
        }
        paritions[n] = sent;

        return paritions;
    }

    template <typename Iter, typename F>
    auto
    parallel(Iter first, Iter sent, F f)
    {
        auto chunked_f = [&](Iter first, Iter sent, F f) { sequential(first, sent, f); };

        std::size_t numProcessingUnits = ThreadExecutor::get_num_exec_unit();

        std::vector<Iter> partitions = __for_each_partitioner(first, sent);

        std::vector<std::thread> threads;
        threads.reserve(numProcessingUnits);

        for (std::size_t i = 0; i != numProcessingUnits; i++)
            threads.emplace_back(std::thread(std::ref(chunked_f), partitions[i], partitions[i + 1], f));

        for (std::size_t i = 0; i != numProcessingUnits; i++)
            threads[i].join();

        return sent;
    }

    template <typename Iter, typename F>
    auto
    sequential(Iter first, Iter sent, F f)
    {
        while (first != sent)
            f(*first++);
        return first;
    }
};
} // namespace __pstl_thread_backend