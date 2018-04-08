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