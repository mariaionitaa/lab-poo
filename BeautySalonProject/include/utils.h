#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>

namespace Beauty_Salon {
    // Structura pentru intervale de timp utilizate in programari
    struct TimeSlot {
        int hour;        // Ora (0-23)
        int minute;      // Minutele (0-59)
        int duration;    // Durata în minute
        
        TimeSlot();
        TimeSlot(int h, int m, int d);
        
        // Verifica daca acest interval se suprapune cu altul
        bool OverlapsWith(const TimeSlot& other) const;
        
        // Converteste intervalul de timp in string pentru afisare
        std::string ToString() const;
    };

    // Structura pentru detaliile serviciilor oferite
    struct ServiceDetails {
        int duration;               
        std::string roomNeeded;     
        bool needsPreparation;      
        
        ServiceDetails();
        ServiceDetails(int dur, const std::string& room, bool prep);
    };

    // Enumerare pentru tipurile de servicii disponibile
    enum class ServiceType {
        HAIR_CUT,     
        HAIR_COLOR,   
        MANICURE,     
        PEDICURE,     
        FACIAL,       
        MASSAGE,      
        OTHER         
    };
}

#endif // UTILS_H