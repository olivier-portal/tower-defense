# Mermaid (mermaid.live)

## Class Diagrams

### Syntax Exemple

```mermaid
---
title: Tower Defense class diagram
---

classDiagram
    class GameObject {
        -String Name
        -int PosX
        -int PosY
        +Despawn() void
    }
    
	Human *-- Cells : composed of
    Salesperson o-- Sales : makes
    Human <|-- Salesperson : is
```

#### Connectors

    <|-- inheritance
    *-- composition
    o-- aggregation
    --> association
    ..> dependency
    ..|> realization
    -- solid link
    .. dashed link
