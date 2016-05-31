#ifndef CIRCULAR_H
#define CIRCULAR_H

#include <string.h>

template <typename buf_type, size_t buf_size> class circular
{
protected:
    buf_type buf[buf_size];
    size_t rpos = 0;
    size_t wpos = 0;

public:
    size_t avail()
    {
        return ((wpos < rpos) ? (buf_size - rpos + wpos) : (wpos - rpos));
    }

    bool add(const buf_type* data, size_t len)
    {
        if (len > buf_size) return false;
        size_t new_wpos = (wpos + len) % buf_size;
        if (new_wpos >= rpos && rpos > wpos) return false; // collision  ----w---r-n---
        if (new_wpos >= rpos && wpos > new_wpos) return false; // collision ---r-n-w---
        if (wpos > new_wpos)  // circular copy ----n---w---
        {
            size_t first_part = buf_size - wpos;
            memcpy(&buf[wpos], data, first_part*sizeof(buf_type));
            if (new_wpos > 0) memcpy(buf, &data[first_part], new_wpos*sizeof(buf_type));
        }
        else // ---w---n---
        {
            memcpy(&buf[wpos], data, len*sizeof(buf_type));
        }
        wpos = new_wpos;
        return true;
    }

    bool add(buf_type data)
    {
        return add(&data, 1);
    }

    size_t get(buf_type* ret, size_t len)
    {
        size_t real = avail();
        if (real == 0) return 0;
        size_t rlen = (len < real) ? len : real;
        size_t new_rpos = (rpos + rlen) % buf_size;
        if (rpos > new_rpos)
        {
            size_t first_part = buf_size - rpos;
            memcpy(ret, &buf[rpos], first_part*sizeof(buf_type));
            if (new_rpos > 0) memcpy(&ret[first_part], buf, new_rpos*sizeof(buf_type));
        }
        else
        {
            memcpy(ret, &buf[rpos], rlen*sizeof(buf_type));
        }
        rpos = new_rpos;
        return rlen;
    }

    buf_type get()
    {
        buf_type ret;
        get(&ret, 1);
        return ret;
    }
};

#endif // CIRCULAR_H
