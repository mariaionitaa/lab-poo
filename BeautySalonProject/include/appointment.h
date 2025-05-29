#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Client.h"
#include "Employee.h"
#include "Service.h"
#include "Utils.h"
#include <string>
#include <ctime>

namespace Beauty_Salon {
    // Enumerare pentru starea programarii
    enum class AppointmentStatus {
        SCHEDULED,      
        IN_PROGRESS,    
        COMPLETED,      
        CANCELLED,      
        NO_SHOW         
    };
    
    // Clasa pentru gestionarea programarilor în salon
    class Appointment {
    private:
        int m_id;                     
        Client m_client;              
        Employee* m_employee;         
        Service* m_service;           
        TimeSlot m_time_slot;         
        AppointmentStatus m_status;   
        std::string m_notes;          
        double m_total_price;         
        bool m_is_confirmed;          
        
    public:
        // Membri statici
        static int m_next_id;  // ID pentru următoarea programare
        static int GenerateID();              
        
        Appointment();
        Appointment(const Client& client, Service* service, const TimeSlot& timeSlot);
        Appointment(const Client& client, Employee* employee, Service* service, const TimeSlot& timeSlot);
        ~Appointment();
        
        // Getteri
        int GetID() const;
        const Client& GetClient() const;
        Employee* GetEmployee() const;
        Service* GetService() const;
        const TimeSlot& GetTimeSlot() const;
        AppointmentStatus GetStatus() const;
        std::string GetNotes() const;
        double GetTotalPrice() const;
        bool IsConfirmed() const;
        
        // Setteri
        void SetEmployee(Employee* employee);
        void SetService(Service* service);
        void SetTimeSlot(const TimeSlot& timeSlot);
        void SetStatus(AppointmentStatus status);
        void AddNotes(const std::string& notes);
        void SetConfirmed(bool confirmed);
        
        // Calculeaza prețul total al programarii, cu tot cu reduceri
        void CalculateTotalPrice();
        
        // Verifica daca programarea poate fi reprogramata, true daca programarea poate fi reprogramata
        bool CanReschedule() const;
        
        // Reprogrameaza programarea pentru un nou interval de timp, true daca reprogramarea a reusit
        bool Reschedule(const TimeSlot& newTimeSlot);
        
        // Anuleaza programarea, true daca anularea a reusit
        bool Cancel();
        
        // Marcheaza programarea ca finalizata, true dacă finalizarea a reusit
        bool Complete();
        
        // Afiseaza informatii despre programare
        void DisplayInfo() const;
        
        // Supraincarcarea operatorului pentru afisare
        friend std::ostream& operator<<(std::ostream& os, const Appointment& appointment);
    };
}

#endif // APPOINTMENT_H