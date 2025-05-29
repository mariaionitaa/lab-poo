#include "Schedule.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

namespace Beauty_Salon {
    // Implementarea constructorilor
    Schedule::Schedule() 
        : m_working_start_hour(9), m_working_end_hour(20), m_max_concurrent_apps(5) {
    }
    
    Schedule::Schedule(int startHour, int endHour, int maxConcurrentApps) 
        : m_working_start_hour(startHour), m_working_end_hour(endHour), m_max_concurrent_apps(maxConcurrentApps) {
    }
    
    // Getteri si setteri
    int Schedule::GetWorkingStartHour() const {
        return m_working_start_hour;
    }
    
    int Schedule::GetWorkingEndHour() const {
        return m_working_end_hour;
    }
    
    int Schedule::GetMaxConcurrentAppointments() const {
        return m_max_concurrent_apps;
    }
    
    void Schedule::SetWorkingHours(int startHour, int endHour) {
        if (startHour >= 0 && startHour < 24 && endHour > startHour && endHour <= 24) {
            m_working_start_hour = startHour;
            m_working_end_hour = endHour;
        }
    }
    
    void Schedule::SetMaxConcurrentAppointments(int max) {
        if (max > 0) {
            m_max_concurrent_apps = max;
        }
    }
    
    // Metode helper private
    bool Schedule::_IsTimeSlotAvailable(const TimeSlot& slot, Employee* employee) const {
        // Verificam daca intervalul de timp se suprapune cu alte programari
        for (const auto& app : m_appointments) {
            // Daca se doreste un angajat specific, verificam doar programarile acelui angajat
            if (employee && app.GetEmployee() != employee) {
                continue;
            }
            
            // Verificam suprapunerea intervalelor de timp
            if (app.GetTimeSlot().OverlapsWith(slot)) {
                // Verificam daca avem mai multe programari simultane decât limita
                int count = 0;
                for (const auto& a : m_appointments) {
                    if (a.GetTimeSlot().OverlapsWith(slot)) {
                        count++;
                    }
                }
                if (count >= m_max_concurrent_apps) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool Schedule::_IsWithinWorkingHours(const TimeSlot& slot) const {
        // Verificam daca intervalul de timp este în programul de lucru
        int endMinutes = slot.hour * 60 + slot.minute + slot.duration;
        int endHour = endMinutes / 60;
        
        return slot.hour >= m_working_start_hour && endHour <= m_working_end_hour;
    }
    
    Employee* Schedule::_FindAvailableEmployee(ServiceType type, const TimeSlot& slot) const {
        return nullptr;
    }
    
    std::vector<TimeSlot> Schedule::_GetAvailableTimeSlots(int date, Service* service) const {
        std::vector<TimeSlot> availableSlots;
        
        // Verificam fiecare interval de 15 minute din ziua respectiva
        int serviceDuration = service->GetDuration();
        
        for (int hour = m_working_start_hour; hour < m_working_end_hour; ++hour) {
            for (int minute = 0; minute < 60; minute += 15) {
                // Verificam daca serviciul poate fi finalizat inainte de inchidere
                TimeSlot slot(hour, minute, serviceDuration);
                int endMinutes = hour * 60 + minute + serviceDuration;
                int endHour = endMinutes / 60;
                
                if (endHour <= m_working_end_hour && _IsTimeSlotAvailable(slot, nullptr)) {
                    availableSlots.push_back(slot);
                }
            }
        }
        
        return availableSlots;
    }
    
    // Metode pentru gestionarea programarilor
    bool Schedule::AddAppointment(const Appointment& appointment) {
        // Verificam daca programarea poate fi adaugata
        if (!_IsWithinWorkingHours(appointment.GetTimeSlot())) {
            return false;
        }
        
        if (!_IsTimeSlotAvailable(appointment.GetTimeSlot(), appointment.GetEmployee())) {
            return false;
        }
        
        // Adaugam programarea
        m_appointments.push_back(appointment);
        
        // Actualizam incarcarea angajatului
        if (appointment.GetEmployee()) {
            int employeeId = appointment.GetEmployee()->GetID();
            if (m_employee_load.find(employeeId) == m_employee_load.end()) {
                m_employee_load[employeeId] = 1;
            } else {
                m_employee_load[employeeId]++;
            }
        }
        
        return true;
    }
    
    bool Schedule::AddAppointment(const Client& client, Service* service, const TimeSlot& timeSlot) {
        // Gasim un angajat disponibil
        Employee* employee = _FindAvailableEmployee(service->GetType(), timeSlot);
        
        // Cream si adaugam o noua programare
        Appointment app(client, employee, service, timeSlot);
        return AddAppointment(app);
    }
    
    bool Schedule::AddAppointment(const Client& client, Employee* employee, Service* service, const TimeSlot& timeSlot) {
        // Cream si adaugam o noua programare
        Appointment app(client, employee, service, timeSlot);
        return AddAppointment(app);
    }
    
    bool Schedule::RemoveAppointment(int id) {
        for (auto it = m_appointments.begin(); it != m_appointments.end(); ++it) {
            if (it->GetID() == id) {
                // Actualizam incarcarea angajatului
                if (it->GetEmployee()) {
                    int employeeId = it->GetEmployee()->GetID();
                    if (m_employee_load[employeeId] > 0) {
                        m_employee_load[employeeId]--;
                    }
                }
                
                // Stergem programarea
                m_appointments.erase(it);
                return true;
            }
        }
        return false;
    }
    
    bool Schedule::UpdateAppointment(int id, const Appointment& newData) {
        // Gasim programarea dupa ID
        Appointment* app = FindAppointment(id);
        if (!app) {
            return false;
        }
        
        // Verificam daca noua programare poate fi adaugata
        if (!_IsWithinWorkingHours(newData.GetTimeSlot())) {
            return false;
        }
        
        if (!_IsTimeSlotAvailable(newData.GetTimeSlot(), newData.GetEmployee())) {
            return false;
        }
        
        // Actualizam incarcarea angajatului vechi
        if (app->GetEmployee()) {
            int oldEmployeeId = app->GetEmployee()->GetID();
            if (m_employee_load[oldEmployeeId] > 0) {
                m_employee_load[oldEmployeeId]--;
            }
        }
        
        // Stergeti programarea veche si adaugati-o pe cea noua
        RemoveAppointment(id);
        return AddAppointment(newData);
    }
    
    Appointment* Schedule::FindAppointment(int id) {
        for (auto& app : m_appointments) {
            if (app.GetID() == id) {
                return &app;
            }
        }
        return nullptr;
    }
    
    // Metode de interogare
    std::vector<Appointment> Schedule::GetAppointmentsByDate(int date) const {
        std::vector<Appointment> result;
        for (const auto& app : m_appointments) {
            if (app.GetTimeSlot().hour == date) {
                result.push_back(app);
            }
        }
        return result;
    }
    
    std::vector<Appointment> Schedule::GetAppointmentsByClient(const Client& client) const {
        std::vector<Appointment> result;
        for (const auto& app : m_appointments) {
            if (app.GetClient().GetName() == client.GetName()) {
                result.push_back(app);
            }
        }
        return result;
    }
    
    std::vector<Appointment> Schedule::GetAppointmentsByEmployee(const Employee& employee) const {
        std::vector<Appointment> result;
        for (const auto& app : m_appointments) {
            if (app.GetEmployee() && app.GetEmployee()->GetName() == employee.GetName()) {
                result.push_back(app);
            }
        }
        return result;
    }
    
    // Algoritm de optimizare a programului
    std::vector<TimeSlot> Schedule::SuggestTimeSlots(const Client& client, Service* service, int preferredDate) const {
        // Gasim toate intervalele disponibile
        std::vector<TimeSlot> availableSlots = _GetAvailableTimeSlots(preferredDate, service);
        
        // Sortam intervalele în functie de ora preferata (daca exista)
        if (preferredDate > 0) {
            std::sort(availableSlots.begin(), availableSlots.end(), 
                [preferredDate](const TimeSlot& a, const TimeSlot& b) {
                    return std::abs(a.hour - preferredDate) < std::abs(b.hour - preferredDate);
                });
        }
        
        // Returnam primele 5 intervale disponibile (sau mai puține dacă nu există 5)
        std::vector<TimeSlot> result;
        for (size_t i = 0; i < std::min(availableSlots.size(), static_cast<size_t>(5)); ++i) {
            result.push_back(availableSlots[i]);
        }
        
        return result;
    }
    
    // Rapoarte si statistici
    void Schedule::GenerateDailyReport(int date) const {
        std::vector<Appointment> dailyApps = GetAppointmentsByDate(date);
        
        std::cout << "=== Daily Report for Hour " << date << " ===" << std::endl;
        std::cout << "Total Appointments: " << dailyApps.size() << std::endl;
        std::cout << "Total Revenue: $" << CalculateDailyRevenue(date) << std::endl;
        
        // Numarul de programari per tip de serviciu
        std::map<std::string, int> serviceCount;
        for (const auto& app : dailyApps) {
            if (app.GetService()) {
                serviceCount[app.GetService()->GetName()]++;
            }
        }
        
        std::cout << "Services breakdown:" << std::endl;
        for (const auto& pair : serviceCount) {
            std::cout << " - " << pair.first << ": " << pair.second << std::endl;
        }
        
        // Status programari
        int scheduled = 0, inProgress = 0, completed = 0, cancelled = 0, noShow = 0;
        for (const auto& app : dailyApps) {
            switch (app.GetStatus()) {
                case AppointmentStatus::SCHEDULED: scheduled++; break;
                case AppointmentStatus::IN_PROGRESS: inProgress++; break;
                case AppointmentStatus::COMPLETED: completed++; break;
                case AppointmentStatus::CANCELLED: cancelled++; break;
                case AppointmentStatus::NO_SHOW: noShow++; break;
            }
        }
        
        std::cout << "Status breakdown:" << std::endl;
        std::cout << " - Scheduled: " << scheduled << std::endl;
        std::cout << " - In Progress: " << inProgress << std::endl;
        std::cout << " - Completed: " << completed << std::endl;
        std::cout << " - Cancelled: " << cancelled << std::endl;
        std::cout << " - No Show: " << noShow << std::endl;
    }
    
    void Schedule::GenerateEmployeeReport(const Employee& employee) const {
        std::vector<Appointment> empApps = GetAppointmentsByEmployee(employee);
        
        std::cout << "=== Employee Report for " << employee.GetName() << " ===" << std::endl;
        std::cout << "Total Appointments: " << empApps.size() << std::endl;
        
        // Calculam veniturile generate de angajat
        double totalRevenue = 0.0;
        for (const auto& app : empApps) {
            totalRevenue += app.GetTotalPrice();
        }
        
        std::cout << "Total Revenue Generated: $" << totalRevenue << std::endl;
        
        // Calculam timpul total lucrat (în minute)
        int totalMinutes = 0;
        for (const auto& app : empApps) {
            totalMinutes += app.GetTimeSlot().duration;
        }
        
        std::cout << "Total Working Time: " 
                 << (totalMinutes / 60) << " hours and " 
                 << (totalMinutes % 60) << " minutes" << std::endl;
    }
    
    double Schedule::CalculateDailyRevenue(int date) const {
        std::vector<Appointment> dailyApps = GetAppointmentsByDate(date);
        
        double total = 0.0;
        for (const auto& app : dailyApps) {
            // Includem doar programarile completate
            if (app.GetStatus() == AppointmentStatus::COMPLETED) {
                total += app.GetTotalPrice();
            }
        }
        
        return total;
    }
    
    // Afisare informatii
    void Schedule::DisplayDailySchedule(int date) const {
        std::vector<Appointment> dailyApps = GetAppointmentsByDate(date);
        
        // Sortam programarile dupa ora
        std::sort(dailyApps.begin(), dailyApps.end(), 
            [](const Appointment& a, const Appointment& b) {
                int timeA = a.GetTimeSlot().hour * 60 + a.GetTimeSlot().minute;
                int timeB = b.GetTimeSlot().hour * 60 + b.GetTimeSlot().minute;
                return timeA < timeB;
            });
        
        std::cout << "=== Schedule for Hour " << date << " ===" << std::endl;
        
        if (dailyApps.empty()) {
            std::cout << "No appointments scheduled." << std::endl;
            return;
        }
        
        for (const auto& app : dailyApps) {
            std::cout << app << std::endl;
        }
    }
    
    void Schedule::DisplayAllAppointments() const {
        if (m_appointments.empty()) {
            std::cout << "No appointments scheduled." << std::endl;
            return;
        }
        
        // Sortam programarile dupa ID
        std::vector<Appointment> sortedApps = m_appointments;
        std::sort(sortedApps.begin(), sortedApps.end(), 
            [](const Appointment& a, const Appointment& b) {
                return a.GetID() < b.GetID();
            });
        
        std::cout << "=== All Appointments ===" << std::endl;
        
        for (const auto& app : sortedApps) {
            std::cout << app << std::endl;
        }
    }
}