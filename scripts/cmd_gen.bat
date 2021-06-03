@rem ==command_generate/==
@rem ==init==
@set make="prm.exe"
@set comp="gmake"
@set iput="--file=nc_gen.prem"
@set oput="--to=nc_gen.make"
@set args=%comp% %iput% %oput%
@rem ==work==
@pushd %root%
@call %make% %args%
@popd
@rem ==quit==
@rem ==/command_generate==
@pause