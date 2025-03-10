# 适配器模式
适配器模式（Adapter Pattern）是一种结构型设计模式，它允许将**不兼容的接口**转换为**客户端期望的接口**。
适配器模式的核心思想是：**通过一个中间层（适配器）来协调两个不兼容的接口，使它们能够一起工作**。

适配器模式可以分为两种实现方式：
1. **类适配器**：    
    - 使用**继承**来实现适配器。        
    - 适配器类继承被适配者，并实现目标接口。        
    - 缺点：由于使用了继承，适配器与被适配者之间的耦合度较高。        
2. **对象适配器**：    
    - 使用**组合**来实现适配器。        
    - 适配器类持有被适配者的引用，并实现目标接口。 
    - 优点：更加灵活，适配器可以适配多个被适配者。


### 适配器模式的应用场景
1. **集成第三方库**：    
    - 当需要使用第三方库，但其接口与现有系统不兼容时，可以使用适配器模式。        
2. **复用旧代码**：    
    - 当需要复用旧的类或模块，但其接口与现有系统不兼容时，可以使用适配器模式。        
3. **统一接口**：   
    - 当需要统一多个类的接口时，可以使用适配器模式。