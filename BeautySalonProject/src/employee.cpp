#include "employee.h"
#include <iostream>

namespace Beauty_Salon {
    // Initializarea membrilor statici
    int Employee::m_total_employees = 0;
    int Employee::m_next_id = 1;
    
    int Employee::GetTotalEmployees() {
        return m_total_employees;
    }
    
    int Employee::GenerateID() {
        return m_next_id++;
    }
    
    // Metode protejate
    void Employee::_AddSpecialization(ServiceType type) {
        // Verificam daca specializarea exista deja
        for (const auto& spec : m_specializations) {
            if (spec == type) return;
        }
        // Adaugam specializarea noua
        m_specializations.push_back(type);
    }
    
    // Implementarea constructorilor
    Employee::Employee() 
        : m_id(GenerateID()), m_name("Unknown"), m_role("General"), m_hourly_rate(15.0) {
        m_total_employees++;
    }
    
    Employee::Employee(const std::string& name) 
        : m_id(GenerateID()), m_name(name), m_role("General"), m_hourly_rate(15.0) {
        m_total_employees++;
    }
    
    Employee::Employee(const std::string& name, const std::string& role, double hourlyRate) 
        : m_id(GenerateID()), m_name(name), m_role(role), m_hourly_rate(hourlyRate) {
        m_total_employees++;
    }
    
    Employee::~Employee() {
        m_total_employees--;
    }
    
    // Getteri si setteri
    int Employee::GetID() const {
        return m_id;
    }
    
    std::string Employee::GetName() const {
        return m_name;
    }
    
    std::string Employee::GetRole() const {
        return m_role;
    }
    
    double Employee::GetHourlyRate() const {
        return m_hourly_rate;
    }
    
    void Employee::SetHourlyRate(double rate) {
        if (rate > 0) {
            m_hourly_rate = rate;
        }
    }
    
    bool Employee::CanProvide(ServiceType type) const {
        for (const auto& spec : m_specializations) {
            if (spec == type) return true;
        }
        return false;
    }
    
    void Employee::DisplayInfo() const {
        std::cout << "Employee: " << m_name << std::endl;
        std::cout << "ID: " << m_id << std::endl;
        std::cout << "Role: " << m_role << std::endl;
        std::cout << "Hourly Rate: $" << m_hourly_rate << std::endl;
        
        std::cout << "Specializations: ";
        if (m_specializations.empty()) {
            std::cout << "None";
        } else {
            for (size_t i = 0; i < m_specializations.size(); ++i) {
                if (i > 0) std::cout << ", ";
                
                // Conversie de la enum la string
                switch (m_specializations[i]) {
                    case ServiceType::HAIR_CUT: std::cout << "Hair Cut"; break;
                    case ServiceType::HAIR_COLOR: std::cout << "Hair Coloring"; break;
                    case ServiceType::MANICURE: std::cout << "Manicure"; break;
                    case ServiceType::PEDICURE: std::cout << "Pedicure"; break;
                    case ServiceType::FACIAL: std::cout << "Facial"; break;
                    case ServiceType::MASSAGE: std::cout << "Massage"; break;
                    default: std::cout << "Other"; break;
                }
            }
        }
        std::cout << std::endl;
    }
    
    std::ostream& operator<<(std::ostream& os, const Employee& employee) {
        os << employee.m_name << " (ID: " << employee.m_id << ", " << employee.m_role << ")";
        return os;
    }
    
    // Implementari Stylist
    Stylist::Stylist() 
        : Employee("", "Stylist", 20.0), m_can_do_coloring(false), m_years_experience(0) {
        _AddSpecialization(ServiceType::HAIR_CUT);
    }
    
    Stylist::Stylist(const std::string& name) 
        : Employee(name, "Stylist", 20.0), m_can_do_coloring(false), m_years_experience(0) {
        _AddSpecialization(ServiceType::HAIR_CUT);
    }
    
    Stylist::Stylist(const std::string& name, double hourlyRate, bool canDoColoring, int yearsExperience) 
        : Employee(name, "Stylist", hourlyRate), m_can_do_coloring(canDoColoring), m_years_experience(yearsExperience) {
        _AddSpecialization(ServiceType::HAIR_CUT);
        if (canDoColoring) {
            _AddSpecialization(ServiceType::HAIR_COLOR);
        }
    }
    
    bool Stylist::CanDoColoring() const {
        return m_can_do_coloring;
    }
    
    void Stylist::SetCanDoColoring(bool canDo) {
        m_can_do_coloring = canDo;
        if (canDo) {
            _AddSpecialization(ServiceType::HAIR_COLOR);
        }
    }
    
    int Stylist::GetExperience() const {
        return m_years_experience;
    }
    
    void Stylist::SetExperience(int years) {
        if (years >= 0) {
            m_years_experience = years;
        }
    }
    
    void Stylist::DisplayInfo() const {
        Employee::DisplayInfo();
        std::cout << "Can Do Coloring: " << (m_can_do_coloring ? "Yes" : "No") << std::endl;
        std::cout << "Years of Experience: " << m_years_experience << std::endl;
    }
    
    // Implementari Technician
    Technician::Technician() 
        : Employee("", "Technician", 18.0), m_is_certified(false) {
    }
    
    Technician::Technician(const std::string& name) 
        : Employee(name, "Technician", 18.0), m_is_certified(false) {
        _AddSpecialization(ServiceType::MANICURE);
        _AddSpecialization(ServiceType::PEDICURE);
    }
    
    Technician::Technician(const std::string& name, double hourlyRate, bool isCertified) 
        : Employee(name, "Technician", hourlyRate), m_is_certified(isCertified) {
        _AddSpecialization(ServiceType::MANICURE);
        _AddSpecialization(ServiceType::PEDICURE);
    }
    
    bool Technician::IsCertified() const {
        return m_is_certified;
    }
    
    void Technician::SetIsCertified(bool certified) {
        m_is_certified = certified;
    }
    
    void Technician::AddCertification(const std::string& certification) {
        m_certifications.push_back(certification);
        if (!m_is_certified && !m_certifications.empty()) {
            m_is_certified = true;
        }
    }
    
    const std::vector<std::string>& Technician::GetCertifications() const {
        return m_certifications;
    }
    
    void Technician::DisplayInfo() const {
        Employee::DisplayInfo();
        std::cout << "Certified: " << (m_is_certified ? "Yes" : "No") << std::endl;
        
        if (!m_certifications.empty()) {
            std::cout << "Certifications:" << std::endl;
            for (const auto& cert : m_certifications) {
                std::cout << " - " << cert << std::endl;
            }
        }
    }
}
