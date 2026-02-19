# Guide do Git - Trabalhando com Branches

## Criação de Branch

Para criar uma nova branch:
```bash
git branch nome-da-branch
```

Para criar uma branch e mudar para ela imediatamente:
```bash
git checkout -b nome-da-branch
```

Ou (Git 2.23+):
```bash
git switch -c nome-da-branch
```

## Listar Branches

Ver todas as branches locais:
```bash
git branch
```

Ver todas as branches (locais e remotas):
```bash
git branch -a
```

## Mudar de Branch

Para trocar para outra branch:
```bash
git checkout nome-da-branch
```

Ou:
```bash
git switch nome-da-branch
```

## Commits

Preparar arquivos para commit:
```bash
git add .                    # Adicionar todos os arquivos
git add arquivo.c            # Adicionar arquivo específico
```

Criar um commit:
```bash
git commit -m "Mensagem descritiva do que foi feito"
```

Ver histórico de commits:
```bash
git log                      # Ver todos os commits
git log --oneline            # Ver de forma condensada
```

## Push e Pull

Enviar uma branch para o repositório remoto:
```bash
git push origin nome-da-branch
```

Se for a primeira vez, use:
```bash
git push -u origin nome-da-branch
```

Trazer atualizações do repositório remoto:
```bash
git pull origin nome-da-branch
```

## Merge de Branches

Fazer merge de uma branch na branch atual:
```bash
git merge nome-da-branch
```

Exemplo - fazer merge de `feature` em `main` (TRAZER AS ATUALIZACOES DA MAIN PARA A SUA BRANCH FEATURE):
```bash
git checkout main
git merge feature
```

## Deletar Branch

Deletar branch local:
```bash
git branch -d nome-da-branch       # Delete seguro
git branch -D nome-da-branch       # Force delete
```

Deletar branch remota:
```bash
git push origin --delete nome-da-branch
```

## Boas Práticas

- **Nomeação de branches**: Use nomes descritivos (ex: `feature/autenticacao`, `fix/bug-password`)
- **Commits frequentes**: Faça commits pequenos e bem descritos
- **Pull antes de push**: Sempre atualize antes de enviar suas mudanças
- **Branch para cada feature**: Crie uma branch nova para cada funcionalidade ou correção
- **Mensagens claras**: Escreva mensagens de commit que expliquem o "por quê", não apenas o "o quê"

## Verificar Status

Ver status atual do repositório:
```bash
git status
```

Ver diferenças entre arquivos modificados:
```bash
git diff
```

## Resumo Rápido do Workflow

```bash
# 1. Criar e mudar para nova branch
git checkout -b feature/minha-funcionalidade

# 2. Trabalhar nos arquivos
# ... editar arquivos ...

# 3. Preparar e fazer commit
git add .
git commit -m "Descrição da mudança"

# 4. Enviar para repositório remoto
git push -u origin feature/minha-funcionalidade

# 5. Fazer merge (geralmente via Pull Request)
git checkout main
git pull origin main
git merge feature/minha-funcionalidade
git push origin main
```
