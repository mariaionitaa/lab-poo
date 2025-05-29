#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include "Utils.h"

namespace Beauty_Salon {
    // Clasa de baza pentru toti angajatii salonului
    class Employee {
    private:
        int m_id;                                
        std::string m_name;                       
        std::string m_role;                       
        double m_hourly_rate;                     
        std::vector<ServiceType> m_specializations; 
        
    protected:
        // Membri statici pentru ID-uri
        static int m_next_id;
        static int GenerateID();
        
        // Metoda protejata pentru adaugarea unei specializari
        void _AddSpecialization(ServiceType type);
        
    public:
        // Membri statici pentru evidenta angajatilor
        static int m_total_employees;
        static int GetTotalEmployees();
        
        // Constructori și destructor
        Employee();
        Employee(const std::string& name);
        Employee(const std::string& name, const std::string& role, double hourlyRate);
        virtual ~Employee();
        
        // Getteri
        int GetID() const;
        std::string GetName() const;
        std::string GetRole() const;
        double GetHourlyRate() const;
        
        // Setteri
        void SetHourlyRate(double rate);
        
        // Verifica daca angajatul poate oferi un anumit tip de serviciu
        bool CanProvide(ServiceType type) const;
        
        // Afiseaza informatii despre angajat
        virtual void DisplayInfo() const;
        
        // Supraincarcarea operatorului de afisare
        friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
    };

    // Subclasa pentru stilisti (coafori, colorare par)
    class Stylist : public Employee {
    private:
        bool m_can_do_coloring;       
        int m_years_experience;       
        
    public:
        // Constructori
        Stylist();
        Stylist(const std::string& name);
        Stylist(const std::string& name, double hourlyRate, bool canDoColoring, int yearsExperience);
        
        // Getteri si setteri
        bool CanDoColoring() const;
        void SetCanDoColoring(bool canDo);
        int GetExperience() const;
        void SetExperience(int years);
        
        // Suprascrierea metodei de afisare
        virtual void DisplayInfo() const override;
    };

    // Subclasa pentru tehnicieni (manichiura, pedichiura, spa)
    class Technician : public Employee {
    private:
        bool m_is_certified;                    
        std::vector<std::string> m_certifications; 
        
    public:
        // Constructori
        Technician();
        Technician(const std::string& name);
        Technician(const std::string& name, double hourlyRate, bool isCertified);
        
        // Getteri si setteri
        bool IsCertified() const;
        void SetIsCertified(bool certified);
        void AddCertification(const std::string& certification);
        const std::vector<std::string>& GetCertifications() const;
        
        // Suprascrierea metodei de afisare
        virtual void DisplayInfo() const override;
    };
}

#endif // EMPLOYEE_H