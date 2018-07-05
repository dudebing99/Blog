[TOC]

------

## API 设计准则

> An API is to the programmer what a GUI is to the end-user. The 'P' in API stands for "Programmer", not "Program", to highlight the fact that APIs are used by programmers, who are humans.
>
> We believe APIs should be minimal and complete, have clear and simple semantics, be intuitive, be easy to memorize, and lead to readable code.
>
> **References:**
>
> [Six Characteristics of Good APIs](https://doc.qt.io/archives/qq/qq13-apis.html#sixcharacteristicsofgoodapis)
>
> [API Design](https://people.mpi-inf.mpg.de/~jblanche/api-design.pdf)

- **Be minimal:** A minimal API is one that has as few public members per class and as few classes as possible. This makes it easier to understand, remember, debug, and change the API.
- **Be complete:** A complete API means the expected functionality should be there. This can conflict with keeping it minimal. Also, if a member function is in the wrong class, many potential users of the function won't find it.
- **Have clear and simple semantics:** As with other design work, you should apply the principle of least surprise. Make common tasks easy. Rare tasks should be possible but not the focus. Solve the specific problem; don't make the solution overly general when this is not needed. 
- **Be intuitive:** As with anything else on a computer, an API should be intuitive. Different experience and background leads to different perceptions on what is intuitive and what isn't. An API is intuitive if a semi-experienced user gets away without reading the documentation, and if a programmer who doesn't know the API can understand code written using it.
- **Be easy to memorize:** To make the API easy to remember, choose a consistent and precise naming convention. Use recognizable patterns and concepts, and avoid abbreviations.
- **Lead to readable code:** Code is written once, but read (and debugged and changed) many times. Readable code may sometimes take longer to write, but saves time throughout the product's life cycle.

## 设计模式的六大原则

- **开闭原则（Open Close Principle）**

  开闭原则的意思是：**对扩展开放，对修改关闭**。在程序需要进行拓展的时候，不能去修改原有的代码，实现一个热插拔的效果。简言之，是为了使程序的扩展性好，易于维护和升级。想要达到这样的效果，我们需要使用接口和抽象类，后面的具体设计中我们会提到这点。

- **里氏代换原则（Liskov Substitution Principle）**

  里氏代换原则是面向对象设计的基本原则之一。 里氏代换原则中说，任何基类可以出现的地方，子类一定可以出现。LSP 是继承复用的基石，只有当派生类可以替换掉基类，且软件单位的功能不受到影响时，基类才能真正被复用，而派生类也能够在基类的基础上增加新的行为。里氏代换原则是对开闭原则的补充。实现开闭原则的关键步骤就是抽象化，而基类与子类的继承关系就是抽象化的具体实现，所以里氏代换原则是对实现抽象化的具体步骤的规范。

- **依赖倒转原则（Dependence Inversion Principle）**

  这个原则是开闭原则的基础，具体内容：针对接口编程，依赖于抽象而不依赖于具体。

- **接口隔离原则（Interface Segregation Principle）**

  这个原则的意思是：使用多个隔离的接口，比使用单个接口要好。它还有另外一个意思是：降低类之间的耦合度。由此可见，其实设计模式就是从大型软件架构出发、便于升级和维护的软件设计思想，它强调降低依赖，降低耦合。

- **迪米特法则，又称最少知道原则（Demeter Principle）**

  最少知道原则是指：一个实体应当尽量少地与其他实体之间发生相互作用，使得系统功能模块相对独立。

- **合成复用原则（Composite Reuse Principle）**

  合成复用原则是指：尽量使用合成/聚合的方式，而不是使用继承。

## 项目管理

### 项目目标

- 狭义上讲，做项目就是要在项目规定的**范围、进度、成本和质量**要求之下完成项目**可交付成果**

- 广义上讲，做项目就是要满足项目相关方在项目上的利益追求，包括已表达出来的需要（Needs）和想要（Wants），以及尚未表达出来的利益期望（Expectations）

  

  各个要素的相互制约关系如下所示

![范围、进度、成本](pic/projectmanagement/scope_progress_cost.png)

> 项目目标，就是在满足相关方需求的前提下，面对来自四面八方的风险，在范围、成本、进度三个因素的约束下保质保量地完成项目的可交付成果。

