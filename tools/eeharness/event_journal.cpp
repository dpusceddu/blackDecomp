#include "event_journal.hpp"
#include <bit>
#include <cstring>

namespace ee {
EventJournal::EventJournal(const std::string& path) {
    static_assert(std::endian::native==std::endian::little);
    file_=gzopen(path.c_str(),"wb1");
    if(!file_)throw Fault("cannot create ordered event journal");
    gzbuffer(file_,1024*1024);buffer_.reserve(1024*1024);
    append("EEEVT001",8);
}
EventJournal::~EventJournal(){if(file_)gzclose(file_);}
void EventJournal::flush(){
    if(!buffer_.empty() && gzwrite(file_,buffer_.data(),unsigned(buffer_.size()))!=int(buffer_.size()))
        throw Fault("cannot write ordered event journal");
    buffer_.clear();
}
void EventJournal::append(const void* data,size_t size){
    if(size>0xffffffffu)throw Fault("oversized external event");
    const auto old=buffer_.size();buffer_.resize(old+size);
    if(size)std::memcpy(buffer_.data()+old,data,size);
    if(buffer_.size()>=1024*1024)flush();
}
void EventJournal::drain(Trace& trace,bool finish){
    if(!file_ || retained_>trace.events.size())throw Fault("event journal continuity lost");
    if(!finish && trace.events.size()<4096)return;
    for(size_t i=retained_;i<trace.events.size();++i){const auto& event=trace.events[i];
        if(event.bytes.size()>0xffffffffu)throw Fault("oversized external event");
        const uint32_t header[]={uint32_t(event.kind),event.pc,event.address,uint32_t(event.bytes.size()),uint32_t(event.default_response)};
        append(header,sizeof(header));append(event.bytes.data(),event.bytes.size());
        static_assert(sizeof(event.arguments)==128 && sizeof(event.float_arguments)==32);
        append(event.arguments.data(),128);append(event.float_arguments.data(),32);++records_;
    }
    if(trace.events.size()>64)trace.events.erase(trace.events.begin(),trace.events.end()-64);
    retained_=trace.events.size();
    if(finish){flush();const int result=gzclose(file_);file_=nullptr;if(result!=Z_OK)throw Fault("cannot finish ordered event journal");}
}
}
