#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "appointment.h"
#include <vector>
#include <map>
#include <memory>

namespace Beauty_Salon {
    // Clasa pentru gestionarea programarilor si optimizarea programului salonului
    class Schedule {
    private:
        std::vector<Appointment> m_appointments;      
        std::map<int, int> m_employee_load;           
        int m_working_start_hour;                     
        int m_working_end_hour;                       
        int m_max_concurrent_apps;                    
        
        // Verifica daca un interval de timp este disponibil pentru programare
        bool _IsTimeSlotAvailable(const TimeSlot& slot, Employee* employee) const;
        
        // Verifica daca un interval de timp este in programul de lucru al salonului
        bool _IsWithinWorkingHours(const TimeSlot& slot) const;
        
        // Gaseste un angajat disponibil pentru un anumit tip de serviciu si interval de timp
        Employee* _FindAvailableEmployee(ServiceType type, const TimeSlot& slot) const;
        
        // Obtine toate intervalele de timp disponibile pentru un serviciu intr-o anumita zi
        std::vector<TimeSlot> _GetAvailableTimeSlots(int date, Service* service) const;
        
    public:
        // Constructori
        Schedule();
        Schedule(int startHour, int endHour, int maxConcurrentApps);
        
        // Getteri
        int GetWorkingStartHour() const;
        int GetWorkingEndHour() const;
        int GetMaxConcurrentAppointments() const;
        
        // Setteri
        void SetWorkingHours(int startHour, int endHour);
        void SetMaxConcurrentAppointments(int max);
        
        // Adauga o programare in sistem
        bool AddAppointment(const Appointment& appointment);
        
        // Adauga o programare in sistem, gasind automat un angajat disponibil
        bool AddAppointment(const Client& client, Service* service, const TimeSlot& timeSlot);
        
        // Adauga o programare in sistem cu un angajat specific
        bool AddAppointment(const Client& client, Employee* employee, Service* service, const TimeSlot& timeSlot);
        
        // Elimina o programare din sistem
        bool RemoveAppointment(int id);
        
        // Actualizeaza datele unei programari existente
        bool UpdateAppointment(int id, const Appointment& newData);
        
        // Gaseste o programare dupa ID
        Appointment* FindAppointment(int id);
        
        // Metode de interogare
        std::vector<Appointment> GetAppointmentsByDate(int date) const;
        std::vector<Appointment> GetAppointmentsByClient(const Client& client) const;
        std::vector<Appointment> GetAppointmentsByEmployee(const Employee& employee) const;
        
        // Algoritm de optimizare a programului - sugereaza intervale optime pentru o programare
        std::vector<TimeSlot> SuggestTimeSlots(const Client& client, Service* service, int preferredDate = 0) const;
        
        // Rapoarte si statistici
        void GenerateDailyReport(int date) const;
        void GenerateEmployeeReport(const Employee& employee) const;
        double CalculateDailyRevenue(int date) const;
        
        // Afisare informatii
        void DisplayDailySchedule(int date) const;
        void DisplayAllAppointments() const;
    };
}

#endif // SCHEDULE_H
