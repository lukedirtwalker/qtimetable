# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       harbour-qtimetable

# >> macros
# << macros

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    QTimeTable Swiss Train Timetable
Version:    0.3
Release:    0
Group:      Qt/Qt
License:    LICENSE
Source0:    %{name}-%{version}.tar.bz2
Source100:  harbour-qtimetable.yaml
Requires:   sailfishsilica-qt5
BuildRequires:  pkgconfig(sailfishapp)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Core)

%description
Short description of my SailfishOS Application


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qtc_qmake5  \
    VERSION='%{version}-%{release}'

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
# << install post

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/86x86/apps/%{name}.png
#%{_datadir}/data/stations.db

# >> files
%changelog
* Mon Oct 27 2014 - Lukas <lukedirtwalker at gamil.com> 0.3-0
-Save stations on exit option added
-Add donation links
-Show version in about page

* Mon Jul 14 2014 - Lukas <lukedirtwalker at gmail.com> 0.2-1
-Nicer UI for station search
-More details in Details page and a nicer UI
-Add a time refresh button
-Nicer station switch button

* Fri Jul 11 2014 - Lukas <lukedirtwalker at gmail.com> 0.1-2
- Add possibility to switch arrival and departure station
- Add a changelog

* Fri Jul 11 2014 - Lukas <lukedirtwalker at gmail.com> 0.1-1
- Initial release

# << files
