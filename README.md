# minishell

## Gestion de Git

> [!IMPORTANT]
> Version sans conflit

1. git Pull remote-friend main
2. git branch new-feature
3. (new-feature) git add . ; git commit
4. git checkout main
5. git pull remote-friend
6. git merge new-feature
7. git push my-remote main
8. git branch -d new-feature
   
```mermaid
   flowchart TB
    A{{Main C0}} --> B[git pull remote
Main C1]
    B -->|git branch new-feature| C[new-feature C0]
    subgraph new-feature
    C --> |git add. ; git commit|D[new-feature
C1]
    end
    D --> |git checkout main|E
    subgraph main
    B ---->E[Main C1]
    E --> |git pull remote-friend| F[Main C2]
    F --> | git merge new-feature| G[Main C3]
    G ==> |git push my-remote| H{{Main C3}}
    H -..- |git branch -d new-feature| I{{Ready for new granch}}
    end
    
```
