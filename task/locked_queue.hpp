//          Copyright hotwatermorning 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace hwm {

namespace detail { namespace ns_task {

//! Producer/Comsumerパターンを実現する
template <class T, class UnderlyingContainer = std::deque<T>>
struct locked_queue
{
	typedef T value_type;
	typedef std::queue<T, UnderlyingContainer> container;

    //! デフォルトコンストラクタ
    locked_queue()
        :   capacity((std::numeric_limits<size_t>::max)())
    {}

    //! コンストラクタ
    /*!
		@param capacity 同時にキュー可能な最大要素数
	*/
    explicit
    locked_queue(size_t capacity)
        :   capacity(capacity)
    {}

    //! @brief キューに要素を追加する。
    /*!
		キューがcapacityまで埋まっている場合は、
		dequeueの呼び出しによって要素が取り除かれるまで処理をブロックする
		@param x キューに追加する要素。
	*/
    void enqueue(T x) {
        std::unique_lock<std::mutex> lock(m);
        c_enq.wait(lock, [this] { return data.size() != capacity; });
        data.push(std::move(x));
        c_deq.notify_one();
    }

	//! キューの先頭から要素の取り出しを試行
	/*!
		キューに要素が入っていた場合は先頭の要素を取り出してtrueを返す。
		そうでなければfalseを返す
		@return 要素を取り出したかどうか
	*/
	bool try_dequeue(T &t)
	{
		std::unique_lock<std::mutex> lock(m);
		if(!data.empty()) {
			t = std::move(data.front());
			data.pop();
			c_enq.notify_one();
			return true;
		} else {
			return false;
		}
	}

    //! @brief キューから値を取り出せるか、指定時刻まで試行する。
    //! @param t キューから取り出した値をムーブ代入で受け取るオブジェクト
    //! @param tp いつまでdequeue処理を試行するかを指定するオブジェクト。std::chrono::time_point型に変換可能でなければならない。
    //! @return 取り出しに成功した場合はtrueが帰る。
    template<class TimePoint>
    bool try_dequeue_until(T &t, TimePoint tp)
    {
        std::unique_lock<std::mutex> lock(m);
        bool const succeeded = 
            c_deq.wait_until(lock, tp, [this] { return !data.empty(); });

        if(succeeded) {
            t = std::move(data.front());
            data.pop();
            c_enq.notify_one();
        }

        return succeeded;
    }

    //! @brief キューから値を取り出せるか、指定時間だけ試行する。
    //! @param t キューから取り出した値をムーブ代入で受け取るオブジェクト
    //! @param tp いつまでdequeue処理を試行するかを指定するオブジェクト。std::chrono::duration型に変換可能でなければならない。
    //! @return 取り出しに成功した場合はtrueが帰る。
    template<class Duration>
    bool try_dequeue_for(T &t, Duration dur)
    {
        return try_dequeue_until(
                t,
                std::chrono::steady_clock::now() + dur);
    }

    //! @brief キューから値を取り出す。
    //! @detail キューが空の場合は、要素が取得できるまで処理をブロックする。
    T dequeue() {
        std::unique_lock<std::mutex> lock(m);
        c_deq.wait(lock, [this] { return !data.empty(); });

        T ret = std::move(data.front());
        data.pop();
        c_enq.notify_one();

		return std::move(ret);
    }

private:
    std::mutex  m;
    container   data;
    size_t      capacity;
    std::condition_variable c_enq;
    std::condition_variable c_deq;
};

}}  //namespace detail::ns_task

}   //namespace hwm
