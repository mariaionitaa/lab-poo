#include "product.h"
#include <iostream>
#include <algorithm>

namespace Beauty_Salon {
    // Initializarea membrului static
    int Product::m_next_id = 1;
    
    int Product::GenerateID() {
        return m_next_id++;
    }
    
    // Implementarea constructorilor
    Product::Product() 
        : m_id(GenerateID()), m_name("Unknown"), m_brand(""), m_price(0.0), 
          m_quantity(0), m_category(ProductCategory::OTHER), 
          m_description(""), m_is_on_sale(false) {
    }
    
    Product::Product(const std::string& name, double price) 
        : m_id(GenerateID()), m_name(name), m_brand(""), m_price(price), 
          m_quantity(0), m_category(ProductCategory::OTHER), 
          m_description(""), m_is_on_sale(false) {
    }
    
    Product::Product(const std::string& name, const std::string& brand, double price, ProductCategory category) 
        : m_id(GenerateID()), m_name(name), m_brand(brand), m_price(price), 
          m_quantity(0), m_category(category), 
          m_description(""), m_is_on_sale(false) {
    }
    
    Product::~Product() {
    }
    
    // Getteri
    int Product::GetID() const {
        return m_id;
    }
    
    std::string Product::GetName() const {
        return m_name;
    }
    
    std::string Product::GetBrand() const {
        return m_brand;
    }
    
    double Product::GetPrice() const {
        return m_price;
    }
    
    int Product::GetQuantity() const {
        return m_quantity;
    }
    
    ProductCategory Product::GetCategory() const {
        return m_category;
    }
    
    std::string Product::GetDescription() const {
        return m_description;
    }
    
    bool Product::IsOnSale() const {
        return m_is_on_sale;
    }
    
    // Setteri
    void Product::SetName(const std::string& name) {
        m_name = name;
    }
    
    void Product::SetBrand(const std::string& brand) {
        m_brand = brand;
    }
    
    void Product::SetPrice(double price) {
        if (price >= 0.0) {
            m_price = price;
        }
    }
    
    void Product::SetQuantity(int quantity) {
        if (quantity >= 0) {
            m_quantity = quantity;
        }
    }
    
    void Product::SetCategory(ProductCategory category) {
        m_category = category;
    }
    
    void Product::SetDescription(const std::string& description) {
        m_description = description;
    }
    
    void Product::SetOnSale(bool onSale) {
        m_is_on_sale = onSale;
    }
    
    // Metode pentru gestionarea stocului
    bool Product::UpdateStock(int quantity) {
        // Verificam daca putem actualiza stocul
        int newQuantity = m_quantity + quantity;
        if (newQuantity < 0) {
            return false;
        }
        
        m_quantity = newQuantity;
        return true;
    }
    
    bool Product::IsInStock() const {
        return m_quantity > 0;
    }
    
    // Implementarea metodei din interfata IDiscountable
    double Product::ApplyDiscount(double amount) {
        // Implementare implicita: aplicam discount-ul direct din pret
        return m_price * (1.0 - amount / 100.0);
    }
    
    // Metode virtuale
    double Product::CalculateFinalPrice() const {
        double price = m_price;
        
        // Daca produsul este la reducere, aplicam un discount de 15%
        if (m_is_on_sale) {
            price *= 0.85; 
        }
        
        return price;
    }
    
    void Product::DisplayInfo() const {
        std::cout << "Product ID: " << m_id << std::endl;
        std::cout << "Name: " << m_name << std::endl;
        if (!m_brand.empty()) {
            std::cout << "Brand: " << m_brand << std::endl;
        }
        std::cout << "Price: $" << m_price;
        if (m_is_on_sale) {
            std::cout << " (Sale: $" << CalculateFinalPrice() << ")";
        }
        std::cout << std::endl;
        
        std::cout << "Category: ";
        switch (m_category) {
            case ProductCategory::HAIR_CARE: std::cout << "Hair Care"; break;
            case ProductCategory::SKIN_CARE: std::cout << "Skin Care"; break;
            case ProductCategory::NAIL_CARE: std::cout << "Nail Care"; break;
            case ProductCategory::MAKEUP: std::cout << "Makeup"; break;
            case ProductCategory::ACCESSORIES: std::cout << "Accessories"; break;
            default: std::cout << "Other"; break;
        }
        std::cout << std::endl;
        
        std::cout << "Quantity in Stock: " << m_quantity << std::endl;
        
        if (!m_description.empty()) {
            std::cout << "Description: " << m_description << std::endl;
        }
    }
    
    // Supraincarcarea operatorului <<
    std::ostream& operator<<(std::ostream& os, const Product& product) {
        os << "Product: " << product.m_name;
        if (!product.m_brand.empty()) {
            os << " (" << product.m_brand << ")";
        }
        os << " - $" << product.m_price;
        if (product.m_is_on_sale) {
            os << " (Sale: $" << product.CalculateFinalPrice() << ")";
        }
        return os;
    }
    
    // Implementari RetailProduct
    RetailProduct::RetailProduct() 
        : Product(), m_retail_markup(0.3), m_is_tester_available(false) {
    }
    
    RetailProduct::RetailProduct(const std::string& name, double price) 
        : Product(name, price), m_retail_markup(0.3), m_is_tester_available(false) {
    }
    
    RetailProduct::RetailProduct(const std::string& name, const std::string& brand, double price, 
                               ProductCategory category, double retailMarkup) 
        : Product(name, brand, price, category), m_retail_markup(retailMarkup), m_is_tester_available(false) {
    }
    
    double RetailProduct::GetRetailMarkup() const {
        return m_retail_markup;
    }
    
    bool RetailProduct::IsTesterAvailable() const {
        return m_is_tester_available;
    }
    
    void RetailProduct::SetRetailMarkup(double markup) {
        if (markup >= 0.0) {
            m_retail_markup = markup;
        }
    }
    
    void RetailProduct::SetTesterAvailable(bool available) {
        m_is_tester_available = available;
    }
    
    double RetailProduct::CalculateFinalPrice() const {
        // Calculam pretul de baza
        double basePrice = Product::CalculateFinalPrice();
        
        // Aplicam adaosul de retail
        return basePrice * (1.0 + m_retail_markup);
    }
    
    void RetailProduct::DisplayInfo() const {
        Product::DisplayInfo();
        std::cout << "Retail Markup: " << (m_retail_markup * 100.0) << "%" << std::endl;
        std::cout << "Tester Available: " << (m_is_tester_available ? "Yes" : "No") << std::endl;
        std::cout << "Final Retail Price: $" << CalculateFinalPrice() << std::endl;
    }
    
    // Implementari ProfessionalProduct
    ProfessionalProduct::ProfessionalProduct() 
        : Product(), m_usage_count(0), m_supplier(""), m_requires_certification(false) {
    }
    
    ProfessionalProduct::ProfessionalProduct(const std::string& name, double price) 
        : Product(name, price), m_usage_count(0), m_supplier(""), m_requires_certification(false) {
    }
    
    ProfessionalProduct::ProfessionalProduct(const std::string& name, const std::string& brand, double price, 
                                           ProductCategory category, const std::string& supplier) 
        : Product(name, brand, price, category), m_usage_count(0), m_supplier(supplier), m_requires_certification(false) {
    }
    
    int ProfessionalProduct::GetUsageCount() const {
        return m_usage_count;
    }
    
    std::string ProfessionalProduct::GetSupplier() const {
        return m_supplier;
    }
    
    bool ProfessionalProduct::RequiresCertification() const {
        return m_requires_certification;
    }
    
    void ProfessionalProduct::SetUsageCount(int count) {
        if (count >= 0) {
            m_usage_count = count;
        }
    }
    
    void ProfessionalProduct::SetSupplier(const std::string& supplier) {
        m_supplier = supplier;
    }
    
    void ProfessionalProduct::SetRequiresCertification(bool requires) {
        m_requires_certification = requires;
    }
    
    // Metode pentru gestionarea utilizarii
    void ProfessionalProduct::IncrementUsage() {
        m_usage_count++;
    }
    
    bool ProfessionalProduct::NeedsReplacement() const {
        // Presupunem ca un produs profesional trebuie inlocuit după 500 de utilizari
        return m_usage_count >= 500;
    }
    
    double ProfessionalProduct::CalculateFinalPrice() const {
        // Calculam pretul de baza
        double basePrice = Product::CalculateFinalPrice();
        
        // Produsele care necesita certificare sunt mai scumpe
        if (m_requires_certification) {
            basePrice *= 1.25; // 25% mai scump
        }
        
        return basePrice;
    }
    
    void ProfessionalProduct::DisplayInfo() const {
        Product::DisplayInfo();
        std::cout << "Supplier: " << (m_supplier.empty() ? "Unknown" : m_supplier) << std::endl;
        std::cout << "Usage Count: " << m_usage_count << std::endl;
        std::cout << "Requires Certification: " << (m_requires_certification ? "Yes" : "No") << std::endl;
        std::cout << "Replacement Status: " << (NeedsReplacement() ? "Needs Replacement" : "OK") << std::endl;
    }
    
    // Implementari ProductBundle
    ProductBundle::ProductBundle() 
        : m_name("Unnamed Bundle"), m_bundle_discount(0.0) {
    }
    
    ProductBundle::ProductBundle(const std::string& name) 
        : m_name(name), m_bundle_discount(10.0) { // 10% discount implicit
    }
    
    ProductBundle::ProductBundle(const std::string& name, double bundleDiscount) 
        : m_name(name), m_bundle_discount(bundleDiscount) {
    }
    
    ProductBundle::~ProductBundle() {
        // Nu eliberam resursele aici deoarece nu detinem produsele
    }
    
    void ProductBundle::AddProduct(Product* product) {
        if (product) {
            m_products.push_back(product);
        }
    }
    
    double ProductBundle::CalculateTotalPrice() const {
        double total = 0.0;
        for (const auto& product : m_products) {
            total += product->CalculateFinalPrice();
        }
        // Aplicam discount-ul pachetului
        return total * (1.0 - m_bundle_discount / 100.0);
    }
    
    void ProductBundle::DisplayBundleInfo() const {
        std::cout << "Bundle: " << m_name << std::endl;
        std::cout << "Discount: " << m_bundle_discount << "%" << std::endl;
        std::cout << "Products included:" << std::endl;
        
        for (const auto& product : m_products) {
            std::cout << " - " << product->GetName() 
                     << " ($" << product->CalculateFinalPrice() << ")" << std::endl;
        }
        
        std::cout << "Total Price: $" << CalculateTotalPrice() << std::endl;
    }
    
    std::ostream& operator<<(std::ostream& os, const ProductBundle& bundle) {
        os << "Bundle: " << bundle.m_name << " - $" << bundle.CalculateTotalPrice() 
           << " (" << bundle.m_products.size() << " products)";
        return os;
    }
    
    // Operatorul + pentru produse
    ProductBundle operator+(const Product& lhs, const Product& rhs) {
        ProductBundle bundle("Custom Bundle");
        // Hack temporar: copiem produsele pentru a le adauga în pachet
        Product* lhsCopy = const_cast<Product*>(&lhs);
        Product* rhsCopy = const_cast<Product*>(&rhs);
        bundle.AddProduct(lhsCopy);
        bundle.AddProduct(rhsCopy);
        return bundle;
    }
}
