Name: liblangtag
Version: 0.5.1
Release: 4%{?dist}
Summary: An interface library to access tags for identifying languages

Group: System Environment/Libraries
License: (LGPLv3+ or MPLv2.0) and UCD
URL: http://tagoh.bitbucket.org/liblangtag/
Source0: https://bitbucket.org/tagoh/%{name}/downloads/%{name}-%{version}.tar.bz2

BuildRequires: gtk-doc
BuildRequires: libtool
BuildRequires: libxml2-devel

%description
%{name} is an interface library to access tags for identifying
languages.

Features:
* several subtag registry database supports:
  - language
  - extlang
  - script
  - region
  - variant
  - extension
  - grandfathered
  - redundant
* handling of the language tags
  - parser
  - matching
  - canonicalizing

%package devel
Summary: Development files for %{name}
Group: Development/Libraries
Requires: %{name}%{?_isa} = %{version}-%{release}

%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%package doc
Summary: Documentation of %{name} API
Group: Documentation
BuildArch: noarch

%description doc
The %{name}-doc package contains documentation files for %{name}.


%prep
%setup -q


%build
%configure --disable-static --enable-shared --disable-introspection
sed -i \
    -e 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' \
    -e 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' \
    libtool
make %{?_smp_mflags} V=1 \
    LD_LIBRARY_PATH=`pwd`/liblangtag/.libs${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}


%install
make install DESTDIR=%{buildroot}
rm -f %{buildroot}/%{_libdir}/*.la %{buildroot}/%{_libdir}/%{name}/*.la


%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%files
%doc AUTHORS COPYING NEWS README
%{_libdir}/%{name}.so.*
%{_libdir}/%{name}/*.so
%{_datadir}/%{name}

%files devel
%{_includedir}/%{name}
%{_libdir}/%{name}.so
%{_libdir}/pkgconfig/%{name}.pc

%files doc
%doc COPYING
%{_datadir}/gtk-doc/html/%{name}


%changelog
* Fri Jan 24 2014 Daniel Mach <dmach@redhat.com> - 0.5.1-4
- Mass rebuild 2014-01-24

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 0.5.1-3
- Mass rebuild 2013-12-27

* Thu May 16 2013 Eike Rathke <erack@redhat.com> - 0.5.1-2-UNBUILT
- updated .spec with MPLv2.0 and UCD licenses

* Tue Apr 30 2013 David Tardon <dtardon@redhat.com> - 0.5.1-1
- fix ABI breakage

* Mon Apr 29 2013 David Tardon <dtardon@redhat.com> - 0.5.0-1
- new release

* Thu Feb 14 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.4.0-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_19_Mass_Rebuild

* Sat Dec 01 2012 David Tardon <dtardon@redhat.com> - 0.4.0-2
- fix build on ppc

* Sun Nov 25 2012 David Tardon <dtardon@redhat.com> - 0.4.0-1
- new upstream release

* Sun Sep 09 2012 David Tardon <dtardon@redhat.com> - 0.3-1
- initial import
