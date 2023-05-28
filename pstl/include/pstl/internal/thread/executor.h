#pragma once

class ThreadExecutor
{
  public:
    static constexpr int
    get_num_exec_unit()
    {
        return 8;
    }
};