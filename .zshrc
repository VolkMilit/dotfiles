# Set up the prompt
#sss
source "$HOME/.config/zsh/git/gitprompt.zsh"
PS1="$(git_super_status) %F{green}[%~]%F{reset_colors}$ " #%F{blue}[%n@%M] 
#PS1="%\C:\%~ > "

#mkdir -m 0700 /dev/cgroup/cpu/user/$$
#echo $$ > /dev/cgroup/cpu/user/$$/tasks

# Use emacs keybindings even if our EDITOR is set to vi
bindkey -e

#settings
setopt histignorealldups sharehistory
setopt autocd
setopt extended_glob
#setopt CORRECT_ALL
setopt  HIST_IGNORE_ALL_DUPS
setopt  HIST_REDUCE_BLANKS

# Keep 1000 lines of history within the shell and save it to ~/.cache/zsh_history:
HISTSIZE=10000
SAVEHIST=1000
HISTFILE=~/.cache/zsh_history

#plugins
source "$HOME/.config/zsh/archive.plugin.zsh"
source "$HOME/.config/zsh/debian.plugin.zsh"
source "$HOME/.config/zsh/directories.zsh"
source "$HOME/.config/zsh/correction.zsh"
source "$HOME/.config/zsh/key-bindings.zsh"
source "$HOME/.config/zsh/alisases.zsh"
source "$HOME/.config/zsh/mount.plugin.zsh"
source "$HOME/.config/zsh/colored-man.plugin.zsh"
source "$HOME/.config/zsh/dircycle.plugin.zsh"
source "$HOME/.config/zsh/notify.plugin.zsh"
source "$HOME/.config/zsh/commandtime.zsh"
source "$HOME/.config/zsh/twily.zsh"

fpath=($HOME/.config/zsh $fpath)

# Use modern completion system
autoload -Uz compinit
compinit

zstyle ':completion:*' auto-description 'specify: %d'
zstyle ':completion:*' completer _expand _complete _correct _approximate
zstyle ':completion:*' format 'Completing %d'
zstyle ':completion:*' group-name ''
zstyle ':completion:*' menu select=2
eval "$(dircolors -b)"
zstyle ':completion:*:default' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' list-prompt %SAt %p: Hit TAB for more, or the character to insert%s
zstyle ':completion:*' matcher-list '' 'm:{a-z}={A-Z}' 'm:{a-zA-Z}={A-Za-z}' 'r:|[._-]=* r:|=* l:|=*'
zstyle ':completion:*' menu select=long
zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
zstyle ':completion:*' use-compctl false

zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'
zstyle ':completion:*:kill:*' command 'ps -u $USER -o pid,%cpu,tty,cputime,cmd'


compctl -k "(one two other possibility)" egrep
