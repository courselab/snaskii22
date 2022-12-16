# Contribuindo para este projeto

## Para contribuir com este projeto alguns padrões devem ser adotados:

 - Usar estratégia de GitFlow branching [1] (e mais uma branch pre-lançamento)

 - Versão semântica 2.0.0 [2]

 - Commits padronizados 1.0.0 [3] (veja os tipos logo abaixo)

 - Sempre tenha um ChangeLog [4]
 
### Enviando contribuições e mudanças

 Primeiro crie uma issue, se não houver nenhuma.

 Faça sua contribuição numa branch de apoio, seguindo o padrão de nome:
 
 'tipo/numero-issue/anotação-descritiva-curta'

 onde 'tipo' é um tipo padronizado de commit.

 Dê submit na sua branch de apoio e marque-a como pull/merge request.
 
 ### Tipos de commit
 
 Selecione um dos tipos apropriados:
 
 - fix: consertando um bug
 - feat: adicionando nova feature
 - build: afeta a build 
 - perf: aperfeçoando um código (além do fix e da feat)
 - doc: modifica documentação interna e/ou externa
 - test: modifica testes
 - tidy: estiliza o código, organização do repositório, altera conformidades padronizadas etc.
 - tmp: branch temporária para outros propósitos

### Considerações adicionais 

A última versão estável do código está na branch _main_. 

Branchs de prerelease (alpha, beta, candidatas e release) ficam na branch _prerelease_.

Se você for selecionado para tratar de uma issue e acredita que não consiguirá finalizá-la a tempo, tente atribuí-la para outra pessoa.

Os arquivos de AUTHORS, NEWS e de ChangeLog devem sempre estar atualizados.

Lembre-se de nunca submeter arquivos desnecessários!

## Referências

[1] https://nvie.com/posts/a-successful-git-branching-model/

[2] https://semver.org/lang/pt-BR/

[3] https://www.conventionalcommits.org/pt-br/v1.0.0/

[4] https://keepachangelog.com/pt-BR/1.0.0/


