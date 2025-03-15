#!bin/bash
IFS=$'\n'

pyenv --version

py_version=$1
py_version_full=$2
venv_root=$3
echo py_version_full $py_version_full
echo venv_root $venv_root

mkdir -p $venv_root
cd $venv_root
# pyenv local $py_version_full

python$py_version -V

venv_name=.venv$py_version_full
python$py_version -m venv $venv_name
source $venv_name/Scripts/activate
python$py_version -m pip install --upgrade pip
pip install -e ../[testing] # --upgrade 
