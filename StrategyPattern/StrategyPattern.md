# 策略模式
策略模式（Strategy Pattern）是一种行为型设计模式，它允许你**定义一系列算法或策略**，并将它们封装在独立的类中，使得它们可以**互相替换**。它允许在运行时选择算法或策略。在 C++中实现策略模式时，可以通过接口或抽象基类来定义一系列算法，然后通过指向不同算法实现的对象指针来动态地选择所需的算法。这种设计使得算法可以在运行时进行更换，而不是在编译时确定。

策略模式的核心思想是：**将算法的使用与算法的实现分离**，使得算法可以独立于客户端变化。

### 策略模式的结构
 策略模式通常包含以下几个角色：
1. **Context（上下文）**：
    - 持有一个策略对象的引用，并通过策略对象执行具体的算法。
    - 上下文通常是一个类，它依赖于策略接口来完成任务。
2. **Strategy（策略接口）**：
    - 定义算法的接口，所有具体策略都需要实现这个接口。
3. **ConcreteStrategy（具体策略）**：
    - 实现策略接口，定义具体的算法。

### 策略模式的应用场景
- 需要动态切换算法。策略模式的设计初衷是为了解决复杂的条件逻辑，当面临的条件很多且具有动态变化的可能时，策略模式能够提供更好的可维护性和扩展性。
- 需要避免使用大量的条件语句。如果面临的条件分支（例如 if-else）固定且数量不多，比如只存在三种情况，并且这些情况不会动态改变，那么使用简单的条件语句可能会更为清晰和直接。
- 需要复用算法。
  
