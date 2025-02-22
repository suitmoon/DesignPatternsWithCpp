# 组合模式
组合模式（Composite Pattern）是一种结构型设计模式，它允许你将对象组合成树形结构来表示“部分-整体”的层次关系。组合模式使得客户端可以统一地处理单个对象和组合对象，而不必关心它们的具体类型。
### 组合模式的核心思想
组合模式的核心思想是将对象组织成树形结构，其中包含两种类型的对象：
1. **叶子节点（Leaf）**：表示树中的叶子对象，没有子节点。
2. **组合节点（Composite）**：表示可以包含子节点的对象，通常包含一组子节点（可以是叶子节点，也可以是其他组合节点）。
通过这种方式，组合模式使得客户端可以一致地处理单个对象和组合对象。
### 组合模式的结构

组合模式通常包含以下几个角色：
1. **Component（抽象组件）**：    
    - 定义叶子节点和组合节点的公共接口。       
    - 可以包含一些默认行为或属性。        
2. **Leaf（叶子节点）**：    
    - 表示树中的叶子对象，没有子节点。        
    - 实现 `Component` 接口。        
3. **Composite（组合节点）**：    
    - 表示可以包含子节点的对象。        
    - 实现 `Component` 接口，并管理子节点（添加、删除、遍历等）。        
4. **Client（客户端）**：    
    - 通过 `Component` 接口操作叶子节点和组合节点。