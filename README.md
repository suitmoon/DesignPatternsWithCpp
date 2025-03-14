对于设计模式，我的理解是，它是在项目中对于代码的复用性以及专注于类对象各个模块间的交互（即分工、合作）中存在的问题所产生的一系列解决方案以及经验总结。 
**提高复用**，重心点在于对变化的理解，即专注于理清变化点与稳定点。  
**提高灵活性（可扩展性/低耦合性）**，通常依赖于分解和抽象。
  - 分解是将一个复杂系统或模块细分成多个更小的、独立的部分，使每一部分职责单一、易于理解和管理。
  - 抽象则是审视依赖关系后，对多个模块相同部分抽取出来，形成接口或抽象类，以便实现不同的具体类。通过这种方式，可以减少代码重复，提高代码的可读性和维护性，同时使系统更容易扩展。
---

**设计模式分三大类**：
**创建型模式:** 涉及对象的创建过程，帮助系统独立于如何创建、组合和表示对象。常见的创建型模式包括：

- [单例模式（Singleton）](./SingletonPattern/SingletonPattern.md)
- [工厂方法模式（Factory Method）](./FactoryPattern/FactoryPattern.md)
- [抽象工厂模式（Abstract Factory）](./FactoryPattern/FactoryPattern.md)
- [建造者模式（Builder）](./BuilderPattern/BuilderPattern.md)
- [原型模式（Prototype）](./PrototypePattern/PrototypePattern.md)

**结构型模式：** 关注类和对象的组合，帮助简化系统结构。典型的结构型模式包括：
- [适配器模式（Adapter）](./AdapterPattern/AdapterPattern.md)
- [桥接模式（Bridge）](./BridgePattern/BridgePattern.md)
- [组合模式（Composite）](./CompositePattern/CompositePattern.md)
- [装饰者模式（Decorator）](./DecoratorPattern/DecoratorPattern.md)
- [外观模式（Facade）](./FacadePattern/FacadePattern.md)
- [享元模式（Flyweight）](./FlyweightPattern/FlyweightPattern.md)
- [代理模式（Proxy）](./ProxyPattern/ProxyPattern.md)

**行为型模式：** 关注对象之间的交互和职责分配，提升对象的协作。常见的行为型模式包括：
- [观察者模式（Observer）](./ObserverPattern/ObserverPattern.md)
- [策略模式（Strategy）](./StrategyPattern/StrategyPattern.md)
- [命令模式（Command）](./CommandPattern/CommandPattern.md)
- [状态模式（State）](./StatePattern/StatePattern.md)
- [责任链模式（Chain of Responsibility）](./ChainOfResponsibilityPattern/ChainOfResponsibilityPattern.md)
- [中介者模式（Mediator）](./MediatorPattern/MediatorPattern.md)
- [访问者模式（Visitor）](./VisitorPattern/VisitorPattern.md)
- [迭代器模式（Iterator）](./IteratorPattern/IteratorPattern.md)
- [模板方法模式（Template Method）](./TemplateMethodPattern/TemplateMethod.md)
- [解释器模式（Interpreter）](./InterpreterPattern/InterpreterPattern.md)
- [备忘录模式（Memento）](./MementoPattern/MementoPattern.md)

从**动态和静态**两个方面来看，设计模式可以分为:
  - 处理类与子类之间的静态关系
  - 处理对象之间的动态关系。
---
设计模式的有效实现尽可能遵循的八大设计原则：
1. **单一职责原则 (SRP)**：
  一个类应该仅有一个职责（变化），职责太多时会导致修改或扩展时，对代码大幅修改造成混乱。通常将职责分离到不同的类中，例如在 MVC（模型-视图-控制器）模式中，模型、视图和控制器各自承担特定职责。
2. **开放封闭原则 (OCP)**：
  对扩展开放，对修改关闭，可以轻松扩展而不需要修改现有代码。比如，通过使用装饰者模式，可以在不改变被装饰对象的情况下添加新功能。  
3. **替换原则 (LSP/里氏替换原则)**：
  子类必须能够替换它的基类（IS-A），继承可以表达类型抽象。
  确保子类能够替换父类而不引入错误。例如在模板方法模式中，子类应能够实现其中定义的算法的一部分而不影响算法的整体功能。
4. **接口隔离原则 (ISP)**：
  使用小而专用的接口，使得实现这些接口的类只需关注自己所关心的功能。例如，观察者模式中的主题和观察者接口。  
5. **依赖倒置原则 (DIP)**：
  高层次的代码（稳定）不应该依赖低层次的代码（变化）、两者都应该依赖于抽象（稳定）；抽象（稳定）不应该依赖实现细节（变化），实现细节应该依赖于抽象（稳定）。  
6. **优先使用对象组合而不是继承。** 
	继承通常会让子类和父类的耦合度增加、组合的方式只要求组件具备良好定义的接口、耦合度低。
7. **封装变化点** 
 设计的目标应该是尽可能将变化控制在一个可控的范围内，以确保这些变化不会对系统的核心功能和稳定性造成影响。通过将不稳定的部分与稳定的部分分离，可以降低系统的复杂性，提高维护性，同时在变化发生时减少对其他部分的影响。
8. **针对接口编程，而不是针对实现** 
	不将变量类型声明为某个特定的具体类，而是声明为某个接口。客户程序无需获知对象的具体类型，只需知道对象所具有的接口；减少系统中各部分的依赖关系，从而实现“高内聚、松耦合”的类型设计方案。






 
