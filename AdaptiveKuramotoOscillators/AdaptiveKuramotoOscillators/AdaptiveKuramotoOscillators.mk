##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=AdaptiveKuramotoOscillators
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/amir/AdaptiveKuramoto/AdaptiveKuramotoOscillators
ProjectPath            :=/home/amir/AdaptiveKuramoto/AdaptiveKuramotoOscillators/AdaptiveKuramotoOscillators
IntermediateDirectory  :=../build-$(ConfigurationName)/AdaptiveKuramotoOscillators
OutDir                 :=../build-$(ConfigurationName)/AdaptiveKuramotoOscillators
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Amir Maghoul
Date                   :=10/10/22
CodeLitePath           :=/home/amir/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/AdaptiveKuramotoOscillators"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/AdaptiveKuramotoOscillators"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/.d:
	@mkdir -p "../build-$(ConfigurationName)/AdaptiveKuramotoOscillators"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/amir/AdaptiveKuramoto/AdaptiveKuramotoOscillators/AdaptiveKuramotoOscillators/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/main.cpp$(PreprocessSuffix) main.cpp

../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(ObjectSuffix): continuum_limit.cpp ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/amir/AdaptiveKuramoto/AdaptiveKuramotoOscillators/AdaptiveKuramotoOscillators/continuum_limit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/continuum_limit.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(DependSuffix): continuum_limit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(DependSuffix) -MM continuum_limit.cpp

../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(PreprocessSuffix): continuum_limit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/continuum_limit.cpp$(PreprocessSuffix) continuum_limit.cpp

../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(ObjectSuffix): discrete_kuramoto.cpp ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/amir/AdaptiveKuramoto/AdaptiveKuramotoOscillators/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/discrete_kuramoto.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(DependSuffix): discrete_kuramoto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(DependSuffix) -MM discrete_kuramoto.cpp

../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(PreprocessSuffix): discrete_kuramoto.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators/discrete_kuramoto.cpp$(PreprocessSuffix) discrete_kuramoto.cpp


-include ../build-$(ConfigurationName)/AdaptiveKuramotoOscillators//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


