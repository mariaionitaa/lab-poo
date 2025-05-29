#include "Service.h"
#include <vector>

namespace Beauty_Salon {
    // Initializare membru static
    int Service::m_total_services_booked = 0;
    
    int Service::GetTotalBookings() {
        return m_total_services_booked;
    }
    
    // Metode protejate
    void Service::_UpdateDetails(const ServiceDetails& details) {
        m_details = details;
    }
    
    // Implementarile constructorilor
    Service::Service() 
        : m_name("Unnamed Service"), m_base_price(0.0), 
          m_details(ServiceDetails()), m_type(ServiceType::OTHER) {
    }
    
    Service::Service(std::string name, double basePrice) 
        : m_name(name), m_base_price(basePrice), 
          m_details(ServiceDetails()), m_type(ServiceType::OTHER) {
    }
    
    Service::Service(std::string name, double basePrice, int durationMinutes) 
        : m_name(name), m_base_price(basePrice), 
          m_details(ServiceDetails(durationMinutes, "", false)), 
          m_type(ServiceType::OTHER) {
    }
    
    Service::Service(std::string name, double basePrice, const ServiceDetails& details) 
        : m_name(name), m_base_price(basePrice), 
          m_details(details), m_type(ServiceType::OTHER) {
    }
    
    Service::~Service() {
    }
    
    // Getteri
    std::string Service::GetName() const {
        return m_name;
    }
    
    double Service::GetBasePrice() const {
        return m_base_price;
    }
    
    ServiceType Service::GetType() const {
        return m_type;
    }
    
    const ServiceDetails& Service::GetDetails() const {
        return m_details;
    }
    
    // Implementarile metodelor din interfete
    double Service::ApplyDiscount(double amount) {
        // Implementare implicita: aplicam discount-ul direct din pret
        return m_base_price * (1.0 - amount / 100.0);
    }
    
    int Service::GetDuration() const {
        return m_details.duration;
    }
    
    bool Service::RequiresSpecialist() const {
        // Implementare implicita: depinde de serviciu
        return false;
    }
    
    // Implementarea metodelor virtuale
    void Service::DisplayInfo() const {
        std::cout << "Service: " << m_name << std::endl;
        std::cout << "Base Price: $" << m_base_price << std::endl;
        std::cout << "Duration: " << m_details.duration << " minutes" << std::endl;
        if (!m_details.roomNeeded.empty()) {
            std::cout << "Required Room: " << m_details.roomNeeded << std::endl;
        }
    }
    
    // Supraincarcare operator pentru afisare
    std::ostream& operator<<(std::ostream& os, const Service& service) {
        os << "Service: " << service.m_name 
           << " - $" << service.m_base_price 
           << " (" << service.m_details.duration << " min)";
        return os;
    }
    
    // Implementari HairService
    HairService::HairService() 
        : Service(), m_includes_washing(false), m_includes_styling(false) {
    }
    
    HairService::HairService(std::string name, double basePrice) 
        : Service(name, basePrice), m_includes_washing(false), m_includes_styling(false) {
        _UpdateDetails(ServiceDetails(30, "Hair Station", false));
    }
    
    HairService::HairService(std::string name, double basePrice, bool washing, bool styling) 
        : Service(name, basePrice), m_includes_washing(washing), m_includes_styling(styling) {
        int duration = 30; 
        if (washing) duration += 15;
        if (styling) duration += 20;
        _UpdateDetails(ServiceDetails(duration, "Hair Station", false));
    }
    
    void HairService::SetIncludesWashing(bool includes) {
        m_includes_washing = includes;
        // Actualizam durata
        ServiceDetails details = GetDetails();
        details.duration += includes ? 15 : -15;
        _UpdateDetails(details);
    }
    
    void HairService::SetIncludesStyling(bool includes) {
        m_includes_styling = includes;
        // Actualizam durata
        ServiceDetails details = GetDetails();
        details.duration += includes ? 20 : -20;
        _UpdateDetails(details);
    }
    
    bool HairService::IncludesWashing() const {
        return m_includes_washing;
    }
    
    bool HairService::IncludesStyling() const {
        return m_includes_styling;
    }
    
    double HairService::CalculatePrice() {
        double price = GetBasePrice();
        if (m_includes_washing) price += 10.0;
        if (m_includes_styling) price += 15.0;
        return price;
    }
    
    int HairService::EstimateTime() {
        // Durata este deja actualizata prin metodele setter
        return GetDuration();
    }
    
    void HairService::DisplayInfo() const {
        Service::DisplayInfo();
        std::cout << "Includes Washing: " << (m_includes_washing ? "Yes" : "No") << std::endl;
        std::cout << "Includes Styling: " << (m_includes_styling ? "Yes" : "No") << std::endl;
    }
    
    // Implementari NailService
    NailService::NailService() 
        : Service(), m_is_gel(false), m_nail_count(10) {
    }
    
    NailService::NailService(std::string name, double basePrice) 
        : Service(name, basePrice), m_is_gel(false), m_nail_count(10) {
        _UpdateDetails(ServiceDetails(45, "Nail Station", false));
    }
    
    NailService::NailService(std::string name, double basePrice, bool isGel, int nailCount) 
        : Service(name, basePrice), m_is_gel(isGel), m_nail_count(nailCount) {
        int duration = isGel ? 60 : 45; // gel dureaza mai mult
        // Ajustam pentru mai putine unghii (daca e cazul)
        if (nailCount < 10) {
            duration = static_cast<int>(duration * (nailCount / 10.0));
        }
        _UpdateDetails(ServiceDetails(duration, "Nail Station", false));
    }
    
    void NailService::SetIsGel(bool isGel) {
        m_is_gel = isGel;
        // Actualizam durata
        ServiceDetails details = GetDetails();
        details.duration = isGel ? 60 : 45;
        // Ajustam pentru numarul de unghii
        if (m_nail_count < 10) {
            details.duration = static_cast<int>(details.duration * (m_nail_count / 10.0));
        }
        _UpdateDetails(details);
    }
    
    void NailService::SetNailCount(int count) {
        m_nail_count = count;
        // Actualizam durata
        ServiceDetails details = GetDetails();
        double baseDuration = m_is_gel ? 60.0 : 45.0;
        details.duration = static_cast<int>(baseDuration * (count / 10.0));
        _UpdateDetails(details);
    }
    
    bool NailService::IsGel() const {
        return m_is_gel;
    }
    
    int NailService::GetNailCount() const {
        return m_nail_count;
    }
    
    double NailService::CalculatePrice() {
        double price = GetBasePrice();
        if (m_is_gel) price *= 1.5; // gel costa mai mult
        // Ajustam pentru mai putine unghii (daca e cazul)
        if (m_nail_count < 10) {
            price = price * (m_nail_count / 10.0);
        }
        return price;
    }
    
    int NailService::EstimateTime() {
        // Durata este deja actualizata prin metodele setter
        return GetDuration();
    }
    
    void NailService::DisplayInfo() const {
        Service::DisplayInfo();
        std::cout << "Gel Service: " << (m_is_gel ? "Yes" : "No") << std::endl;
        std::cout << "Nail Count: " << m_nail_count << std::endl;
    }
    
    // Implementari SpaService
    SpaService::SpaService() 
        : Service(), m_is_premium(false), m_requires_special_room(false) {
    }
    
    SpaService::SpaService(std::string name, double basePrice) 
        : Service(name, basePrice), m_is_premium(false), m_requires_special_room(false) {
        _UpdateDetails(ServiceDetails(60, "Spa Room", true));
    }
    
    SpaService::SpaService(std::string name, double basePrice, bool isPremium, bool requiresSpecialRoom) 
        : Service(name, basePrice), m_is_premium(isPremium), m_requires_special_room(requiresSpecialRoom) {
        std::string room = requiresSpecialRoom ? "Premium Spa Room" : "Spa Room";
        int duration = isPremium ? 90 : 60;
        _UpdateDetails(ServiceDetails(duration, room, true));
    }
    
    void SpaService::SetIsPremium(bool isPremium) {
        m_is_premium = isPremium;
        // Actualizam durata și camera
        ServiceDetails details = GetDetails();
        details.duration = isPremium ? 90 : 60;
        if (m_requires_special_room) {
            details.roomNeeded = "Premium Spa Room";
        }
        _UpdateDetails(details);
    }
    
    void SpaService::SetRequiresSpecialRoom(bool requires) {
        m_requires_special_room = requires;
        // Actualizam camera
        ServiceDetails details = GetDetails();
        details.roomNeeded = requires ? "Premium Spa Room" : "Spa Room";
        _UpdateDetails(details);
    }
    
    bool SpaService::IsPremium() const {
        return m_is_premium;
    }
    
    bool SpaService::RequiresSpecialRoom() const {
        return m_requires_special_room;
    }
    
    double SpaService::CalculatePrice() {
        double price = GetBasePrice();
        if (m_is_premium) price *= 1.75; // premium costa mai mult
        if (m_requires_special_room) price += 30.0; // camera speciala are cost suplimentar
        return price;
    }
    
    int SpaService::EstimateTime() {
        // Durata este deja actualizata prin metodele setter
        return GetDuration();
    }
    
    void SpaService::DisplayInfo() const {
        Service::DisplayInfo();
        std::cout << "Premium Service: " << (m_is_premium ? "Yes" : "No") << std::endl;
        std::cout << "Special Room Required: " << (m_requires_special_room ? "Yes" : "No") << std::endl;
    }
    
    // Implementari ServicePackage
    ServicePackage::ServicePackage() 
        : m_name("Unnamed Package"), m_package_discount(0.0) {
    }
    
    ServicePackage::ServicePackage(const std::string& name) 
        : m_name(name), m_package_discount(10.0) { // 10% discount implicit
    }
    
    ServicePackage::ServicePackage(const std::string& name, double packageDiscount) 
        : m_name(name), m_package_discount(packageDiscount) {
    }
    
    ServicePackage::~ServicePackage() {
        // Nu eliberam resursele aici deoarece nu detinem serviciile
    }
    
    void ServicePackage::AddService(Service* service) {
        m_services.push_back(service);
    }
    
    double ServicePackage::CalculateTotalPrice() const {
        double total = 0.0;
        for (const auto& service : m_services) {
            total += service->CalculatePrice();
        }
        // Aplicam discount-ul pachetului
        return total * (1.0 - m_package_discount / 100.0);
    }
    
    int ServicePackage::CalculateTotalTime() const {
        int total = 0;
        for (const auto& service : m_services) {
            total += service->EstimateTime();
        }
        return total;
    }
    
    void ServicePackage::DisplayPackageInfo() const {
        std::cout << "Package: " << m_name << std::endl;
        std::cout << "Discount: " << m_package_discount << "%" << std::endl;
        std::cout << "Services included:" << std::endl;
        
        for (const auto& service : m_services) {
            std::cout << " - " << service->GetName() 
                     << " ($" << service->CalculatePrice() << ")" << std::endl;
        }
        
        std::cout << "Total Price: $" << CalculateTotalPrice() << std::endl;
        std::cout << "Total Duration: " << CalculateTotalTime() << " minutes" << std::endl;
    }
    
    std::ostream& operator<<(std::ostream& os, const ServicePackage& package) {
        os << "Package: " << package.m_name << " - $" << package.CalculateTotalPrice() 
           << " (" << package.CalculateTotalTime() << " min, " 
           << package.m_services.size() << " services)";
        return os;
    }
    
    // Operatorul + pentru servicii
    ServicePackage operator+(const Service& lhs, const Service& rhs) {
        ServicePackage package("Custom Package");
        // Hack temporar: copiem serviciile pentru a le adăuga în pachet
        Service* lhsCopy = const_cast<Service*>(&lhs);
        Service* rhsCopy = const_cast<Service*>(&rhs);
        package.AddService(lhsCopy);
        package.AddService(rhsCopy);
        return package;
    }
}