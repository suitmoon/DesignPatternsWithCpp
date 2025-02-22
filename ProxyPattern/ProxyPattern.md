# 代理模式
代理模式（Proxy Pattern）是一种结构型设计模式，它允许你提供一个代理对象来控制对另一个对象的访问。代理对象通常会在客户端和目标对象之间起到中介作用，可以在不改变目标对象的情况下，增加额外的功能或控制访问，比如权限检查、延迟加载、日志记录等。
代理模式的核心思想是：**通过引入一个代理对象，间接访问目标对象**。
### 代理模式的结构
代理模式通常包含以下几个角色：
1. **Subject（抽象主题）**：
    - 定义目标对象和代理对象的共同接口。
    - 客户端通过这个接口与目标对象或代理对象交互。 
2. **RealSubject（真实主题）**：
    - 实际的目标对象，代理对象最终会调用它的方法。 
    - 它通常包含核心的业务逻辑。 
3. **Proxy（代理）**：    
    - 代理对象，它持有对真实主题的引用。       
    - 在调用真实主题的方法之前或之后，代理可以执行一些额外的操作（如权限检查、缓存等）。
### 代理模式的应用场景
1. **权限控制**：    
    - 控制用户对某些资源的访问权限，比如只有管理员才能访问某些页面。        
2. **延迟初始化**：    
    - 当创建一个对象的开销很大时，可以使用代理来延迟对象的初始化。        
3. **缓存**：    
    - 缓存请求的结果，避免重复计算或请求。        
4. **日志记录**：    
    - 在访问对象时，代理可以记录日志。        
5. **远程访问**：    
    - 代理可以隐藏与远程对象通信的复杂性。
    