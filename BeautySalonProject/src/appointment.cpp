#include "Appointment.h"
#include <iostream>
#include <ctime>

namespace Beauty_Salon {
    // Initializarea membrului static
    int Appointment::m_next_id = 1;
    
    int Appointment::GenerateID() {
        return m_next_id++;
    }
    
    // Implementarea constructorilor
    Appointment::Appointment() 
        : m_id(GenerateID()), m_client(), m_employee(nullptr), m_service(nullptr),
          m_time_slot(), m_status(AppointmentStatus::SCHEDULED), m_notes(""),
          m_total_price(0.0), m_is_confirmed(false) {
    }
    
    Appointment::Appointment(const Client& client, Service* service, const TimeSlot& timeSlot) 
        : m_id(GenerateID()), m_client(client), m_employee(nullptr), m_service(service),
          m_time_slot(timeSlot), m_status(AppointmentStatus::SCHEDULED), m_notes(""),
          m_total_price(0.0), m_is_confirmed(false) {
        
        // Calculam pretul total
        CalculateTotalPrice();
    }
    
    Appointment::Appointment(const Client& client, Employee* employee, Service* service, const TimeSlot& timeSlot) 
        : m_id(GenerateID()), m_client(client), m_employee(employee), m_service(service),
          m_time_slot(timeSlot), m_status(AppointmentStatus::SCHEDULED), m_notes(""),
          m_total_price(0.0), m_is_confirmed(false) {
        
        // Calculam pretul total
        CalculateTotalPrice();
    }
    
    Appointment::~Appointment() {
        // Nu eliberam resursele employee si service deoarece nu le detinem
    }
    
    // Getteri
    int Appointment::GetID() const {
        return m_id;
    }
    
    const Client& Appointment::GetClient() const {
        return m_client;
    }
    
    Employee* Appointment::GetEmployee() const {
        return m_employee;
    }
    
    Service* Appointment::GetService() const {
        return m_service;
    }
    
    const TimeSlot& Appointment::GetTimeSlot() const {
        return m_time_slot;
    }
    
    AppointmentStatus Appointment::GetStatus() const {
        return m_status;
    }
    
    std::string Appointment::GetNotes() const {
        return m_notes;
    }
    
    double Appointment::GetTotalPrice() const {
        return m_total_price;
    }
    
    bool Appointment::IsConfirmed() const {
        return m_is_confirmed;
    }
    
    // Setteri
    void Appointment::SetEmployee(Employee* employee) {
        m_employee = employee;
        // Recalculam pretul daca se schimba angajatul
        CalculateTotalPrice();
    }
    
    void Appointment::SetService(Service* service) {
        m_service = service;
        // Actualizam durata programarii in functie de serviciu
        if (service) {
            m_time_slot.duration = service->GetDuration();
        }
        // Recalculam prețul
        CalculateTotalPrice();
    }
    
    void Appointment::SetTimeSlot(const TimeSlot& timeSlot) {
        m_time_slot = timeSlot;
    }
    
    void Appointment::SetStatus(AppointmentStatus status) {
        m_status = status;
    }
    
    void Appointment::AddNotes(const std::string& notes) {
        if (!m_notes.empty()) {
            m_notes += "\n";
        }
        m_notes += notes;
    }
    
    void Appointment::SetConfirmed(bool confirmed) {
        m_is_confirmed = confirmed;
    }
    
    // Metode pentru gestionarea programarii
    void Appointment::CalculateTotalPrice() {
        if (m_service) {
            // Calculam pretul serviciului
            double basePrice = m_service->CalculatePrice();
            
            // Aplicam discount-ul clientului (daca exista)
            m_total_price = m_client.ApplyDiscount(basePrice);
        } else {
            m_total_price = 0.0;
        }
    }
    
    bool Appointment::CanReschedule() const {
        // Verificam daca programarea poate fi reprogramata, (doar daca statusul este SCHEDULED sau CANCELLED)
        return (m_status == AppointmentStatus::SCHEDULED || 
                m_status == AppointmentStatus::CANCELLED);
    }
    
    bool Appointment::Reschedule(const TimeSlot& newTimeSlot) {
        if (CanReschedule()) {
            m_time_slot = newTimeSlot;
            // Daca programarea era anulata, o readucem la scheduled
            if (m_status == AppointmentStatus::CANCELLED) {
                m_status = AppointmentStatus::SCHEDULED;
            }
            return true;
        }
        return false;
    }
    
    bool Appointment::Cancel() {
        // Verificam daca programarea poate fi anulata
        if (m_status == AppointmentStatus::SCHEDULED || 
            m_status == AppointmentStatus::IN_PROGRESS) {
            m_status = AppointmentStatus::CANCELLED;
            return true;
        }
        return false;
    }
    
    bool Appointment::Complete() {
        // Verificam dacă programarea poate fi marcata ca finalizata
        if (m_status == AppointmentStatus::SCHEDULED || 
            m_status == AppointmentStatus::IN_PROGRESS) {
            m_status = AppointmentStatus::COMPLETED;
            
            // Adaugam o vizită clientului
            const_cast<Client&>(m_client).AddVisit();
            
            return true;
        }
        return false;
    }
    
    // Afisare informatii
    void Appointment::DisplayInfo() const {
        std::cout << "Appointment #" << m_id << std::endl;
        std::cout << "Client: " << m_client.GetName() << std::endl;
        if (m_employee) {
            std::cout << "Employee: " << m_employee->GetName() << std::endl;
        } else {
            std::cout << "Employee: Not assigned" << std::endl;
        }
        if (m_service) {
            std::cout << "Service: " << m_service->GetName() << std::endl;
        } else {
            std::cout << "Service: Not specified" << std::endl;
        }
        std::cout << "Time: " << m_time_slot.ToString() << std::endl;
        
        // Afisare status
        std::cout << "Status: ";
        switch (m_status) {
            case AppointmentStatus::SCHEDULED: std::cout << "Scheduled"; break;
            case AppointmentStatus::IN_PROGRESS: std::cout << "In Progress"; break;
            case AppointmentStatus::COMPLETED: std::cout << "Completed"; break;
            case AppointmentStatus::CANCELLED: std::cout << "Cancelled"; break;
            case AppointmentStatus::NO_SHOW: std::cout << "No Show"; break;
        }
        std::cout << std::endl;
        
        std::cout << "Confirmed: " << (m_is_confirmed ? "Yes" : "No") << std::endl;
        std::cout << "Total Price: $" << m_total_price << std::endl;
        
        if (!m_notes.empty()) {
            std::cout << "Notes: " << m_notes << std::endl;
        }
    }
    
    // Supraincarcarea operatorului <<
    std::ostream& operator<<(std::ostream& os, const Appointment& appointment) {
        os << "App #" << appointment.m_id << " - ";
        os << appointment.m_client.GetName();
        
        if (appointment.m_service) {
            os << " - " << appointment.m_service->GetName();
        }
        
        os << " at " << appointment.m_time_slot.ToString();
        
        // Status in format scurt
        os << " [";
        switch (appointment.m_status) {
            case AppointmentStatus::SCHEDULED: os << "SCH"; break;
            case AppointmentStatus::IN_PROGRESS: os << "INP"; break;
            case AppointmentStatus::COMPLETED: os << "COM"; break;
            case AppointmentStatus::CANCELLED: os << "CAN"; break;
            case AppointmentStatus::NO_SHOW: os << "NOS"; break;
        }
        os << "]";
        
        return os;
    }
}