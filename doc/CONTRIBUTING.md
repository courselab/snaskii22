# Contributing to this project

This document needs to be properly edited.

## Meanwhile, these are some essencial notes

 To keep things consistent, we adhere to some standards

 - GitFlow branching strategy [1] (plus a prerelease branch)

 - Semantic versioning 2.0.0 [2]

 - Conventional Commits 1.0.0 [3] (see types bellow)

 - Keep a ChangeLog [4]
 
### Submitting changes

 
 First create and issue, if one does not exist yet.
 
 Develop your contribution in a support branch, following the naming scheme
 
 'type/issue-number/short-descriptive-annotation'

 where 'type' is a conventional commit type.
 
 Submit your support branch and mark it as a pull/merge request.
 
 ### Commit types
 
 Select the appropriate type.
 
 - fix: fix a bug
 - feat: add new feature
 - build: affect the build 
 - perf: improve code (other than fix and feat)
 - doc: modify internal or external modification
 - test: modify tests
 - tidy: code style, repo organization, standard compliance etc.
 - tmp: a temporary branch for some other purpose

### Further directions

Latest stable releases reside in the _main_ branch.

Prerelease (alpha, beta, release candidates) reside on branch _prerelease_.

If you are developer and is assigned an issue but you believe you are not
able to handle timely, please, try to reassign it to someone else.

AUTHORS, NEWS and ChangeLog files should be kept up-to-date.

It should be needless to say, but do not commit unnecessary files.

## References

[1] https://nvie.com/posts/a-successful-git-branching-model/

[2] https://semver.org/

[3] https://www.conventionalcommits.org/en/v1.0.0/

[4] https://keepachangelog.com/en/1.0.0/


