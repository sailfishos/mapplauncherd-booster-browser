Name:       mapplauncherd-booster-browser
Summary:    Application launch booster for Sailfish Browser
Version:    0.0.1
Release:    1
License:    LGPLv2
URL:        https://github.com/sailfishos/mapplauncherd-booster-browser
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  pkgconfig(applauncherd) >= 4.2.3
BuildRequires:  pkgconfig(qdeclarative5-boostable)
BuildRequires:  pkgconfig(Qt0Feedback)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Sql)
BuildRequires:  pkgconfig(Qt5Svg)
BuildRequires:  pkgconfig(Qt5WaylandClient)
BuildRequires:  pkgconfig(Qt5Xml)
BuildRequires:  pkgconfig(Qt5XmlPatterns)
BuildRequires:  pkgconfig(libshadowutils)
BuildRequires:  pkgconfig(mlite5)
BuildRequires:  pkgconfig(ngf-qt5)
BuildRequires:  pkgconfig(gio-2.0)
BuildRequires:  pkgconfig(gmodule-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(timed-qt5)
BuildRequires:  systemd

# Browser booster specific
BuildRequires:  pkgconfig(qt5embedwidget)

Requires(pre):  shadow-utils
Requires:  sailfishsilica-qt5 >= 0.11.55
Requires:  mapplauncherd >= 4.2.3
Requires:  systemd-user-session-targets

%description
%{summary}.

%prep
%autosetup -n %{name}-%{version}

%build
# We intentionally disable LD_AS_NEEDED in order to be able to link to libraries that we do not use symbols from.
unset LD_AS_NEEDED
%qmake5

%make_build

%install
%qmake_install

mkdir -p %{buildroot}%{_userunitdir}/user-session.target.wants || true
ln -s ../booster-browser.service %{buildroot}%{_userunitdir}/user-session.target.wants/

%pre
groupadd -rf privileged

%files
%defattr(-,root,root,-)
%license COPYING.LESSER
%attr(2755, root, privileged) %{_libexecdir}/mapplauncherd/booster-browser
%{_datadir}/booster-browser/*
%{_userunitdir}/booster-browser.service
%{_userunitdir}/booster-browser@.service
%{_userunitdir}/user-session.target.wants/booster-browser.service
