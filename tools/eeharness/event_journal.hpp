#pragma once
#include "ee.hpp"
#include <zlib.h>

namespace ee {
// Capture-mode history is streamed instead of retained for an entire campaign.
// This does not alter function replay/equivalence traces.
class EventJournal {
public:
    explicit EventJournal(const std::string& path);
    ~EventJournal();
    EventJournal(const EventJournal&)=delete;
    EventJournal& operator=(const EventJournal&)=delete;
    void drain(Trace&,bool finish=false);
    uint64_t records() const { return records_; }
private:
    gzFile file_ = nullptr;
    std::vector<uint8_t> buffer_;
    size_t retained_ = 0;
    uint64_t records_ = 0;
    void append(const void*,size_t);
    void flush();
};
}
