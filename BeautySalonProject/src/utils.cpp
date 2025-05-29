#include "Utils.h"
#include <sstream>
#include <iomanip>

namespace Beauty_Salon {
    // Implementarea TimeSlot
    TimeSlot::TimeSlot() : hour(0), minute(0), duration(0) {}
    
    TimeSlot::TimeSlot(int h, int m, int d) : hour(h), minute(m), duration(d) {}
    
    bool TimeSlot::OverlapsWith(const TimeSlot& other) const {
        // Convertim totul in minute pentru calcule mai usoare
        int thisStart = hour * 60 + minute;
        int thisEnd = thisStart + duration;
        
        int otherStart = other.hour * 60 + other.minute;
        int otherEnd = otherStart + other.duration;
        
        // Verificam daca intervalele se suprapun
        return (thisStart < otherEnd) && (otherStart < thisEnd);
    }
    
    std::string TimeSlot::ToString() const {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hour << ":" 
           << std::setfill('0') << std::setw(2) << minute 
           << " (" << duration << " min)";
        return ss.str();
    }

    // Implementarea ServiceDetails
    ServiceDetails::ServiceDetails() 
        : duration(0), roomNeeded(""), needsPreparation(false) {}
    
    ServiceDetails::ServiceDetails(int dur, const std::string& room, bool prep) 
        : duration(dur), roomNeeded(room), needsPreparation(prep) {}
}